// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityMetar.h"
#include "objects/Color.h"
#include "common/GlobalVariables.h"
#include "util/To.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityMath.h"
#include "util/UtilityString.h"

const QString UtilityMetar::metarFileName = "/us_metar3.txt";
const QString UtilityMetar::pattern1 = ".*? (M?../M?..) .*?";
const QString UtilityMetar::pattern2 = ".*? A([0-9]{4})";
const QString UtilityMetar::pattern3 = "AUTO ([0-9].*?KT) .*?";
const QString UtilityMetar::pattern4 = "Z ([0-9].*?KT) .*?";
const QString UtilityMetar::pattern5 = "SM (.*?) M?[0-9]{2}/";
bool UtilityMetar::initializedObsMap = false;
QHash<QString, LatLon> UtilityMetar::obsLatlon;
QStringList UtilityMetar::metarDataRaw;
QVector<RID> UtilityMetar::metarSites;

RID UtilityMetar::findClosestObservation(const LatLon& latLon) {
    const auto lines = UtilityIO::rawFileToStringArray(GlobalVariables::resDir + metarFileName);
    QVector<RID> metarSites;
    for (auto i : UtilityList::range(lines.size())) {
        auto tmpArr = lines[i].split(' ');
        if (tmpArr.size() > 2) {
            metarSites.push_back(RID(tmpArr[0], LatLon(tmpArr[1], tmpArr[2])));
        }
    }
    auto shortestDistance = 1000.00;
    auto bestIndex = -1;
    for (auto i : UtilityList::range(metarSites.size())) {
        const auto currentDistance = latLon.dist(metarSites[i].location);
        metarSites[i].distance = currentDistance;
        if (currentDistance < shortestDistance) {
            shortestDistance = currentDistance;
            bestIndex = i;
        }
    }
    if (bestIndex == -1) {
        return metarSites[0];
    } else {
        return metarSites[bestIndex];
    }
}

void UtilityMetar::getStateMetarArrayForWXOGL(const QString& radarSite, FileStorage& fileStorage) {
    if (fileStorage.obsDownloadTimer.isRefreshNeeded() || radarSite != fileStorage.obsOldRadarSite) {
        QStringList obsAl;
        QStringList obsAlExt;
        QStringList obsAlWb;
        QStringList obsAlWbGust;
        QVector<float> obsAlX;
        QVector<float> obsAlY;
        QVector<int> obsAlAviationColor;
        fileStorage.obsOldRadarSite = radarSite;
        const auto obsList = getObservationSites(radarSite);
        const auto url = GlobalVariables::nwsAWCwebsitePrefix + "/adds/metars/index?submit=1&station_ids=" + obsList + "&chk_metars=on";
        const auto html = UtilityIO::getHtml(url);
        const auto htmlColumn = UtilityString::parseColumn(html, "<FONT FACE=\"Monospace,Courier\">(.*?)</FONT><BR>");
        const auto metarArr = condenseObs(htmlColumn);
        if (!initializedObsMap) {
            const auto lines = UtilityIO::rawFileToStringArray(GlobalVariables::resDir + metarFileName);
            // _ = lines.popLast();
            for (const auto& line : lines) {
                const auto items = line.split(" ");
                obsLatlon[items[0]] = LatLon(items[1], items[2]);
            }
            initializedObsMap = true;
        }
        for (const auto& metar : metarArr) {
            if ((metar.startsWith("K") || metar.startsWith("P")) && !metar.contains("NIL")) {
                auto validWind = false;
                auto validWindGust = false;
                const auto metarItems = metar.split(" ");
                const auto TDArr = UtilityString::parse(metar, pattern1).split("/");
                const auto timeBlob = (metarItems.size() > 1) ? metarItems[1] : "";
                auto pressureBlob = UtilityString::parse(metar, pattern2);
                auto windBlob = UtilityString::parse(metar, pattern3);
                if (windBlob == "") {
                    windBlob = UtilityString::parse(metar, pattern4);
                }
                const auto conditionsBlob = UtilityString::parse(metar, pattern5);
                auto visBlob = UtilityString::parse(metar, " ([0-9].*?SM) ");
                auto visBlobArr = visBlob.split(" ");
                auto visBlobDisplay = visBlobArr[visBlobArr.size() - 1];
                visBlob = visBlobArr[visBlobArr.size() - 1].replace("SM", "");
                auto visInt = 0;
                if (visBlob.contains("/")) {
                    visInt = 0;
                } else if (visBlob != "") {
                    visInt = To::Int(visBlob);
                } else {
                    visInt = 20000;
                }
                auto ovcStr = UtilityString::parse(conditionsBlob, "OVC([0-9]{3})");
                auto bknStr = UtilityString::parse(conditionsBlob, "BKN([0-9]{3})");
                auto ovcInt = 100000;
                auto bknInt = 100000;
                if (ovcStr != "") {
                    ovcStr += "00";
                    ovcInt = To::Int(ovcStr);
                }
                if (bknStr != "") {
                    bknStr += "00";
                    bknInt = To::Int(bknStr);
                }
                auto lowestCig = (bknInt < ovcInt) ? bknInt : ovcInt;
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
                    pressureBlob = UtilityString::insert(pressureBlob, pressureBlob.size() - 2, ".");
                    pressureBlob = UtilityMath::unitsPressure(pressureBlob);
                }
                QString windDir = "";
                QString windInKt = "";
                QString windGustInKt = "";
                if (windBlob.contains("KT") && windBlob.size() == 7) {
                    validWind = true;
                    windDir = UtilityString::substring(windBlob, 0, 3);
                    windInKt = UtilityString::substring(windBlob, 3, 5);
                    windBlob = windDir + " (" + UtilityMath::convertWindDir(windDir) + ") " + windInKt + " kt";
                } else if (windBlob.contains("KT") && windBlob.size() == 10) {
                    validWind = true;
                    validWindGust = true;
                    windDir = UtilityString::substring(windBlob, 0, 3);
                    windInKt = UtilityString::substring(windBlob, 3, 5);
                    windGustInKt = UtilityString::substring(windBlob, 6, 8);
                    windBlob = windDir + " (" + UtilityMath::convertWindDir(windDir) + ") " + windInKt + " G " + windGustInKt + " kt";
                }
                if (TDArr.size() > 1) {
                    QString temperature = TDArr[0];
                    QString dewPoint = TDArr[1];
                    temperature = UtilityMath::celsiusToFahrenheit(temperature.replace("M", "-")).replace(".0", "");
                    dewPoint = UtilityMath::celsiusToFahrenheit(dewPoint.replace("M", "-")).replace(".0", "");
                    QString obsSite = metarItems[0];
                    auto latlon = obsLatlon.value(obsSite, LatLon(0.0, 0.0));
                    latlon.lonString = latlon.lonString.replace("-0", "-");
                    obsAl.push_back(latlon.latString + ":" + latlon.lonString + ":" + temperature + "/" + dewPoint);
                    obsAlExt.push_back(latlon.latString + ":" + latlon.lonString + ":" + temperature + "/" + dewPoint + " (" + obsSite + ")" + GlobalVariables::newline + pressureBlob + " - " + visBlobDisplay + GlobalVariables::newline + windBlob + GlobalVariables::newline + conditionsBlob + GlobalVariables::newline + timeBlob);
                    if (validWind) {
                        obsAlWb.push_back(latlon.latString + ":" + latlon.lonString + ":" + windDir + ":" + windInKt);
                        obsAlX.push_back(latlon.lat);
                        obsAlY.push_back(latlon.lon * -1.0);
                        obsAlAviationColor.push_back(aviationColor);
                    }
                    if (validWindGust) {
                        obsAlWbGust.push_back(latlon.latString + ":" + latlon.lonString + ":" + windDir + ":" + windGustInKt);
                    }
                }
            }
        }
        fileStorage.obsArr.clear();
        fileStorage.obsArr = obsAl;
        fileStorage.obsArrExt.clear();
        fileStorage.obsArrExt = obsAlExt;
        fileStorage.obsArrWb.clear();
        fileStorage.obsArrWb = obsAlWb;
        fileStorage.obsArrWbGust.clear();
        fileStorage.obsArrWbGust = obsAlWbGust;
        fileStorage.obsArrX.clear();
        fileStorage.obsArrX = obsAlX;
        fileStorage.obsArrY.clear();
        fileStorage.obsArrY = obsAlY;
        fileStorage.obsArrAviationColor.clear();
        fileStorage.obsArrAviationColor = obsAlAviationColor;
    }
}

QString UtilityMetar::getObservationSites(const QString& radarSite) {
    QString obsListSb = "";
    const auto radarLocation = LatLon::fromRadarSite(radarSite);
    readMetarData();
    const float obsSiteRange = 200.0;
    for (const auto& site : metarSites) {
        const auto currentDistance = radarLocation.dist(site.location);
        if (currentDistance < obsSiteRange) {
            obsListSb += site.name + ",";
        }
    }
    return obsListSb.replace(",$", "");
}

void UtilityMetar::readMetarData() {
    if (metarDataRaw.size() == 0) {
        metarDataRaw = UtilityIO::rawFileToStringArray(GlobalVariables::resDir + metarFileName);
        metarSites.clear();
        for (const auto& metar : metarDataRaw) {
            const auto items = metar.split(" ");
            metarSites.push_back(RID(items[0], LatLon(items[1], items[2])));
        }
    }
}

// used to condense a list of metar that contains multiple entries for one site,
// newest is first so simply grab first/append
QStringList UtilityMetar::condenseObs(const QStringList& observations) {
    QHash<QString, bool> siteMap;
    QStringList goodObsList;
    for (const auto& ob : observations) {
        auto items = ob.split(" ");
        if (items.size() > 3) {
            if (!siteMap.contains(items[0])) {
                siteMap[items[0]] = true;
                goodObsList.push_back(ob);
            }
        }
    }
    return goodObsList;
}
