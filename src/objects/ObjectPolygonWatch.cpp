// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/ObjectPolygonWatch.h"
#include "common/GlobalVariables.h"
#include "objects/Color.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityDownload.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"
#include "WString.h"

unordered_map<PolygonType, std::unique_ptr<ObjectPolygonWatch>> ObjectPolygonWatch::polygonDataByType;
DataStorage ObjectPolygonWatch::watchLatlonCombined{"WATCH_LATLON_COMBINED"};
const unordered_map<PolygonType, string> ObjectPolygonWatch::namesByEnumId{
    {Mcd, "mcd"},
    {Mpd, "mpd"},
    {Watch, "watch"},
    {WatchTornado, "watchTornado"},
};
const vector<PolygonType> ObjectPolygonWatch::polygonList{
    Watch,
    WatchTornado,
    Mcd,
    Mpd
};
const unordered_map<PolygonType, int> ObjectPolygonWatch::colorDefaultByType{
    {Mcd, Color::rgb(153, 51, 255)},
    {Mpd, Color::rgb(0, 255, 0)},
    {Watch, Color::rgb(255, 187, 0)},
    {WatchTornado, Color::rgb(255, 0, 0)},
};
const unordered_map<PolygonType, string> ObjectPolygonWatch::colorPrefByType{
    {Mcd, "RADAR_COLOR_MCD"},
    {Mpd, "RADAR_COLOR_MPD"},
    {Watch, "RADAR_COLOR_TSTORM_WATCH"},
    {WatchTornado, "RADAR_COLOR_TOR_WATCH"},
};

ObjectPolygonWatch::ObjectPolygonWatch(PolygonType type)
    : type{ type }
    , storage{ DataStorage{getPrefTokenStorage()} }
    , latLonList{ DataStorage{getPrefTokenLatLon()} }
    , numberList{ DataStorage{getPrefTokenNumberList()} }
    , timer{ DownloadTimer{"WATCH_" + getTypeName()} }
    , colorInt { Utility::readPrefInt(colorPrefByType.at(type), colorDefaultByType.at(type)) }
    , isEnabled{ WString::startsWith(Utility::readPref(prefTokenEnabled(), "false"), "t") }
{
    storage.update();
    latLonList.update();
    numberList.update();
}

void ObjectPolygonWatch::download() {
    if (timer.isRefreshNeeded()) {
        const auto html = UtilityIO::getHtml(getUrl());
        storage.setValue(html);
        if (type == Mpd) {
            string numberListString;
            string latLonString;
            const auto numbers = UtilityString::parseColumn(storage.getValue(), ">MPD #(.*?)</a></strong>");
            for (const auto& numberStr : numbers) {
                const auto num = To::Int(numberStr);
                const auto numberModified = To::stringPadLeftZeros(num, 4);
                const auto text = UtilityDownload::getTextProduct("WPCMPD" + numberModified);
                numberListString += numberModified + ":";
                latLonString += LatLon::storeWatchMcdLatLon(text);
            }
            latLonList.setValue(latLonString);
            numberList.setValue(numberListString);
        } else if (type == Mcd) {
            string numberListString;
            string latLonString;
            const auto numbers = UtilityString::parseColumn(html, "<strong><a href=./products/md/md.....html.>Mesoscale Discussion #(.*?)</a></strong>");
            for (const auto& numberStr : numbers) {
                const auto num = To::Int(numberStr);
                const auto numberModified = To::stringPadLeftZeros(num, 4);
                const auto text = UtilityDownload::getTextProduct("SPCMCD" + numberModified);
                numberListString += numberModified + ":";
                latLonString += LatLon::storeWatchMcdLatLon(text);
            }
            latLonList.setValue(latLonString);
            numberList.setValue(numberListString);
        } else if (type == Watch) {
            string numberListString;
            string latLonString;
            string latLonTorString;
            string latLonCombinedString;
            const auto numbers = UtilityString::parseColumn(html, "[om] Watch #([0-9]*?)</a>");
            for (const auto& numberStr : numbers) {
                numberListString += To::stringPadLeftZeros(numberStr, 4) + ":";
                const auto text = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/wou" + To::stringPadLeftZeros(numberStr, 4) + ".html");
                const auto preText = UtilityString::parseMultiLineLastMatch(text, GlobalVariables::pre2Pattern);
                if (WString::contains(preText, "SEVERE TSTM")) {
                    latLonString += LatLon::storeWatchMcdLatLon(preText);
                } else {
                    latLonTorString += LatLon::storeWatchMcdLatLon(preText);
                }
                latLonCombinedString += LatLon::storeWatchMcdLatLon(preText);
            }
            latLonList.setValue(latLonString);
            numberList.setValue(numberListString);
            polygonDataByType[WatchTornado]->latLonList.setValue(latLonTorString);
            watchLatlonCombined.setValue(latLonCombinedString);
        }
    }
}

// KEEP
// QString ObjectPolygonWatch::getData() {
//    return storage.getValue();
// }

string ObjectPolygonWatch::getUrl() const {
    string downloadUrl;
    if (type == Mcd) {
        downloadUrl = GlobalVariables::nwsSPCwebsitePrefix + "/products/md/";
    } else if (type == Watch) {
        downloadUrl = GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/";
    } else if (type == WatchTornado) {
        downloadUrl = GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/";
    } else if (type == Mpd) {
        downloadUrl = GlobalVariables::nwsWPCwebsitePrefix + "/metwatch/metwatch_mpd.php";
    }
    return downloadUrl;
}

void ObjectPolygonWatch::update() {
    isEnabled = WString::startsWith(Utility::readPref(prefTokenEnabled(), "false"), "t");
    colorInt = Utility::readPrefInt(colorPrefByType.at(type), colorDefaultByType.at(type));
}

string ObjectPolygonWatch::getPrefTokenStorage() const {
    return "SEVERE_DASHBOARD_" + getTypeName();
}

string ObjectPolygonWatch::prefTokenEnabled() const {
    return "RADAR_SHOW_" + WString::toUpper(getTypeName());
}

// KEEP
// QString ObjectPolygonWatch::getPrefTokenColor() {
//    return "RADAR_COLOR_" + getTypeName();
// }

string ObjectPolygonWatch::getPrefTokenNumberList() const {
    return getTypeName() + "_NO_LIST";
}

string ObjectPolygonWatch::getPrefTokenLatLon() const {
    return getTypeName() + "_LATLON";
}

string ObjectPolygonWatch::getTypeName() const {
    return namesByEnumId.at(type);
}

void ObjectPolygonWatch::load() {
    for (auto& data : polygonList) {
        if (polygonDataByType.count(data) == 0) {
            polygonDataByType[data] = std::make_unique<ObjectPolygonWatch>(data);
        } else {
            polygonDataByType[data]->update();
        }
    }
    polygonDataByType[WatchTornado]->isEnabled = polygonDataByType[Watch]->isEnabled;
}

// KEEP
// QString ObjectPolygonWatch::storeWatchMcdLatLon(QString html) {
//    auto coordinates = UtilityString::parseColumn(html, "([0-9]{8}).*?");
//    QString value = "";
//    for (const auto& coordinate : coordinates) {
//        auto latLon = ObjectPolygonWatch::getLatLonFromString(coordinate);
//        value += latLon.printSpaceSeparated();
//    }
//    value += ":";
//    return value.replace(" :", ":");
// }

// KEEP
// 36517623 is 3651 -7623
// LatLon ObjectPolygonWatch::getLatLonFromString(QString latLonString) {
//    const auto latString = latLonString.left(4);
//    const auto lonString = latLonString.right(4);
//    auto lat = To::Double(latString);
//    auto lon = To::Double(lonString);
//    lat /= 100.0;
//    lon /= 100.0;
//    if (lon < 40.0) {
//        lon += 100.0;
//    }
//    return LatLon{lat, -1.0 * lon};
// }

string ObjectPolygonWatch::getLatLon(const string& number) {
    const auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/wou" + number + ".html");
    return UtilityString::parseMultiLineLastMatch(html, GlobalVariables::pre2Pattern);
}
