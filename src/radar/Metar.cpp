// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/Metar.h"
#include <QDebug>
#include "objects/Color.h"
#include "common/GlobalVariables.h"
#include "util/To.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityMath.h"
#include "util/UtilityString.h"
#include "objects/WString.h"

const string Metar::metarFileName{"/us_metar3.txt"};
bool Metar::initializedObsMap{false};
unordered_map<string, LatLon> Metar::obsLatlon;
vector<string> Metar::metarDataRaw;
vector<RID> Metar::metarSites;
std::mutex Metar::mtx;

void Metar::getStateMetarArrayForWXOGL(const string& radarSite, FileStorage& fileStorage) {
    if (fileStorage.obsDownloadTimer.isRefreshNeeded() || radarSite != fileStorage.obsOldRadarSite) {
        vector<string> obsAl;
        vector<string> obsAlExt;
        vector<string> obsAlWb;
        vector<string> obsAlWbGust;
        vector<double> obsAlX;
        vector<double> obsAlY;
        vector<int> obsAlAviationColor;
        fileStorage.obsOldRadarSite = radarSite;
        const auto obsList = getNearbyObsSites(radarSite);

        const auto url = "https://aviationweather.gov/cgi-bin/data/metar.php?ids=" + obsList;
        const auto html = UtilityIO::getHtml(url);
        const auto metarsTmp = WString::split(html, GlobalVariables::newline);
        const auto metarArr = condenseObs(metarsTmp);
        mtx.lock();
        if (!initializedObsMap) {
            const auto lines = UtilityIO::rawFileToStringArray(GlobalVariables::resDir + metarFileName);
            for (const auto& line : lines) {
                const auto items = WString::split(line, " ");
                obsLatlon[items[0]] = LatLon{items[1], items[2]};
            }
            initializedObsMap = true;
        }
        mtx.unlock();
        for (const auto& metar : metarArr) {
            if ((WString::startsWith(metar, "K") || WString::startsWith(metar, "P")) && !WString::contains(metar, "NIL")) {
                auto validWind = false;
                auto validWindGust = false;
                const auto metarItems = WString::split(metar, " ");
                const auto tmpBlob = UtilityString::parse(metar, ".*? (M?../M?..) .*?");
                const auto tempAndDewpointList = WString::split(tmpBlob, "/");
                const auto timeBlob = (metarItems.size() > 1) ? metarItems[1] : "";
                auto pressureBlob = UtilityString::parse(metar, ".*? A([0-9]{4})");
                auto windBlob = UtilityString::parse(metar, "AUTO ([0-9].*?KT) .*?");
                if (windBlob.empty()) {
                    windBlob = UtilityString::parse(metar, "Z ([0-9].*?KT) .*?");
                }
                const auto conditionsBlob = UtilityString::parse(metar, "SM (.*?) M?[0-9]{2}/");
                auto visBlob = UtilityString::parse(metar, " ([0-9].*?SM) ");
                const auto visBlobArr = WString::split(visBlob, " ");
                string visBlobDisplay;
                if (!visBlobArr.empty()) {
                    visBlobDisplay = visBlobArr[visBlobArr.size() - 1];
                    visBlob = visBlobArr[visBlobArr.size() - 1];
                    visBlob = WString::replace(visBlob, "SM", "");
                }
                auto visInt = 20000;
                if (WString::contains(visBlob, "/")) {
                    visInt = 0;
                } else if (!visBlob.empty()) {
                    visInt = To::Int(visBlob);
                }
                auto ovcStr = UtilityString::parse(conditionsBlob, "OVC([0-9]{3})");
                auto bknStr = UtilityString::parse(conditionsBlob, "BKN([0-9]{3})");
                auto ovcInt = 100000;
                auto bknInt = 100000;
                if (!ovcStr.empty()) {
                    ovcStr += "00";
                    ovcInt = To::Int(ovcStr);
                }
                if (!bknStr.empty()) {
                    bknStr += "00";
                    bknInt = To::Int(bknStr);
                }
                auto lowestCig = bknInt < ovcInt ? bknInt : ovcInt;
                auto aviationColor = Color::GREEN;
                if (visInt > 5 && lowestCig > 3000) {
                    aviationColor = Color::GREEN;
                }
                if ((visInt >= 3 && visInt <= 5) || (lowestCig >= 1000 && lowestCig <= 3000)) {
                    aviationColor = Color::rgb(0, 100, 255);
                }
                if ((visInt >= 1 && visInt < 3) || (lowestCig >= 500 && lowestCig < 1000)) {
                    aviationColor = Color::RED;
                }
                if (visInt < 1 || lowestCig < 500) {
                    aviationColor = Color::MAGENTA;
                }
                if (pressureBlob.size() == 4) {
                    pressureBlob = UtilityString::insert(pressureBlob, static_cast<int>(pressureBlob.size()) - 2, ".");
                    pressureBlob = UtilityMath::unitsPressure(pressureBlob);
                }
                string windDir;
                string windInKt;
                string windGustInKt;
                if (WString::contains(windBlob, "KT") && windBlob.size() == 7) {
                    validWind = true;
                    windDir = UtilityString::substring(windBlob, 0, 3);
                    windInKt = UtilityString::substring(windBlob, 3, 5);
                    windBlob = windDir + " (" + UtilityMath::convertWindDir(windDir) + ") " + windInKt + " kt";
                } else if (WString::contains(windBlob, "KT") && windBlob.size() == 10) {
                    validWind = true;
                    validWindGust = true;
                    windDir = UtilityString::substring(windBlob, 0, 3);
                    windInKt = UtilityString::substring(windBlob, 3, 5);
                    windGustInKt = UtilityString::substring(windBlob, 6, 8);
                    windBlob = windDir + " (" + UtilityMath::convertWindDir(windDir) + ") " + windInKt + " G " + windGustInKt + " kt";
                }
                if (tempAndDewpointList.size() > 1) {
                    auto temperature = tempAndDewpointList[0];
                    auto dewPoint = tempAndDewpointList[1];
                    temperature = WString::replace(temperature, "M", "-");
                    temperature = UtilityMath::celsiusToFahrenheit(temperature);
                    temperature = WString::split(temperature, ".")[0];
                    dewPoint = WString::replace(dewPoint, "M", "-");
                    dewPoint = UtilityMath::celsiusToFahrenheit(dewPoint);
                    dewPoint = WString::split(dewPoint, ".")[0];
                    const auto& obsSite = metarItems[0];
                    LatLon latlon;
                    if (obsLatlon.find(obsSite) == obsLatlon.end()) {
                        // return "Not Present";
                    } else {
                        latlon = obsLatlon[obsSite];
                    }
                    latlon.setLonStr(WString::replace(latlon.lonStr(), "-0", "-"));
                    obsAl.push_back(latlon.latStr() + ":" + latlon.lonStr() + ":" + temperature + "/" + dewPoint);
                    obsAlExt.push_back(latlon.latStr() + ":" + latlon.lonStr() + ":" + temperature + "/" + dewPoint + " (" + obsSite + ")" + GlobalVariables::newline + pressureBlob + " - " + visBlobDisplay + GlobalVariables::newline + windBlob + GlobalVariables::newline + conditionsBlob + GlobalVariables::newline + timeBlob);
                    if (validWind) {
                        obsAlWb.push_back(latlon.latStr() + ":" + latlon.lonStr() + ":" + windDir + ":" + windInKt);
                        obsAlX.push_back(latlon.lat());
                        obsAlY.push_back(latlon.lon() * -1.0);
                        obsAlAviationColor.push_back(aviationColor);
                    }
                    if (validWindGust) {
                        obsAlWbGust.push_back(latlon.latStr() + ":" + latlon.lonStr() + ":" + windDir + ":" + windGustInKt);
                    }
                }
            }
        }
        fileStorage.obsArr = obsAl;
        fileStorage.obsArrExt = obsAlExt;
        fileStorage.obsArrWb = obsAlWb;
        fileStorage.obsArrWbGust = obsAlWbGust;
        fileStorage.obsArrX = obsAlX;
        fileStorage.obsArrY = obsAlY;
        fileStorage.obsArrAviationColor = obsAlAviationColor;
    }
}

string Metar::getNearbyObsSites(const string& radarSite) {
    string obsListSb;
    const auto radarLocation = LatLon::fromRadarSite(radarSite);
    readMetarData();
    const auto obsSiteRange = 200.0;
    for (const auto& site : metarSites) {
        const auto currentDistance = radarLocation.dist(site.location);
        if (currentDistance < obsSiteRange) {
            obsListSb += site.name + ",";
        }
    }
    return WString::replace(obsListSb, ",$", "");
}

void Metar::readMetarData() {
    if (metarDataRaw.empty()) {
        metarDataRaw = UtilityIO::rawFileToStringArray(GlobalVariables::resDir + metarFileName);
        metarSites.clear();
        for (const auto& metar : metarDataRaw) {
            const auto items = WString::split(metar, " ");
            if (items.size() > 2) {
                metarSites.emplace_back(items[0], LatLon{items[1], items[2]}, 0.0);
            }
        }
    }
}

// used to condense a list of metar that contains multiple entries for one site,
// newest is first so simply grab first/append
vector<string> Metar::condenseObs(const vector<string>& observations) {
    unordered_map<string, bool> siteMap;
    vector<string> goodObsList;
    for (const auto& ob : observations) {
        const auto items = WString::split(ob, " ");
        if (items.size() > 3) {
            if (siteMap.find(items[0]) == siteMap.end()) {
                siteMap[items[0]] = true;
                goodObsList.push_back(ob);
            }
        }
    }
    return goodObsList;
}

RID Metar::findClosestObservation(const LatLon& latLon, int index) {
    readMetarData();
    vector<RID> obsSites{metarSites};
    for (auto i : range(obsSites.size())) {
        obsSites[i].distance = latLon.dist(obsSites[i].location);
    }
    std::sort(
        obsSites.begin(),
        obsSites.end(),
        [] (const RID &s1, const RID &s2) { return s1.distance < s2.distance; });
    return obsSites[index];
}
