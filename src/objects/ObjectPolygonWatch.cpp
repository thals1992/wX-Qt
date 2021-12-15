// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
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

QHash<PolygonType, ObjectPolygonWatch *> ObjectPolygonWatch::polygonDataByType;
DataStorage ObjectPolygonWatch::watchLatlonCombined = DataStorage("WATCH_LATLON_COMBINED");

const QStringList ObjectPolygonWatch::namesByEnumId = {
    "none",
    "mcd",
    "mpd",
    "watch",
    "watchTornado",
    "tst",
    "tor",
    "ffw",
    "spotter",
    "spotterLabels",
    "windBarbGusts",
    "windBarb",
    "windBarbCircle",
    "locationDot",
    "locationDotCircle",
    "sti",
    "tvs",
    "hi",
    "observations",
    "swo",
    "smw",
    "sqw",
    "dsw",
    "sps",
    "mws",
};

const QVector<PolygonType> ObjectPolygonWatch::polygonList = {
    PolygonType::watch,
    PolygonType::watchTornado,
    PolygonType::mcd,
    PolygonType::mpd
};

ObjectPolygonWatch::ObjectPolygonWatch() {
}

ObjectPolygonWatch::ObjectPolygonWatch(PolygonType type1) {
    this->type1 = type1;
    isEnabled = Utility::readPref(getPrefTokenEnabled(), "false").startsWith("t");
    storage = DataStorage(getPrefTokenStorage());
    storage.update();
    latLonList = DataStorage(getPrefTokenLatLon());
    latLonList.update();
    numberList = DataStorage(getPrefTokenNumberList());
    numberList.update();
    timer = DownloadTimer("WATCH_" + getTypeName());
}

void ObjectPolygonWatch::download() {
    if (timer.isRefreshNeeded()) {
        const auto html = UtilityIO::getHtml(getUrl());
        storage.setValue(html);
        if (type1 == PolygonType::mpd) {
            QString numberListString = "";
            QString latLonString = "";
            const auto numbers = UtilityString::parseColumn(storage.getValue(), ">MPD #(.*?)</a></strong>");
            for (const auto& numberStr : numbers) {
                auto num = To::Int(numberStr);
                const auto numberModified = To::StringPadLeftZeros(num, 4);
                const auto text = UtilityDownload::getTextProduct("WPCMPD" + numberModified);
                numberListString += numberModified + ":";
                latLonString += LatLon::storeWatchMcdLatLon(text);
            }
            latLonList.setValue(latLonString);
            numberList.setValue(numberListString);
        }
        else if (type1 == PolygonType::mcd) {
            QString numberListString = "";
            QString latLonString = "";
            const auto numbers = UtilityString::parseColumn(html, "<strong><a href=./products/md/md.....html.>Mesoscale Discussion #(.*?)</a></strong>");
            for (const auto& numberStr : numbers) {
                int num = To::Int(numberStr);
                const auto numberModified = To::StringPadLeftZeros(num, 4);
                const auto text = UtilityDownload::getTextProduct("SPCMCD" + numberModified);
                numberListString += numberModified + ":";
                latLonString += LatLon::storeWatchMcdLatLon(text);
            }
            latLonList.setValue(latLonString);
            numberList.setValue(numberListString);
        }
        else if (type1 == PolygonType::watch) {
            QString numberListString = "";
            QString latLonString = "";
            QString latLonTorString = "";
            QString latLonCombinedString = "";
            const auto numbers = UtilityString::parseColumn(html, "[om] Watch #([0-9]*?)</a>");
            for (const auto& numberStr : numbers) {
                numberListString += To::StringPadLeftZeros(numberStr, 4) + ":";
                const auto text = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/wou" + To::StringPadLeftZeros(numberStr, 4) + ".html");
                const auto preText = UtilityString::parseMultiLineLastMatch(text, GlobalVariables::pre2Pattern);
                if (preText.contains("SEVERE TSTM")) {
                    latLonString += LatLon::storeWatchMcdLatLon(preText);
                } else {
                    latLonTorString += LatLon::storeWatchMcdLatLon(preText);
                }
                latLonCombinedString += LatLon::storeWatchMcdLatLon(preText);
            }
            latLonList.setValue(latLonString);
            numberList.setValue(numberListString);
            ObjectPolygonWatch::polygonDataByType[PolygonType::watchTornado]->latLonList.setValue(latLonTorString);
            ObjectPolygonWatch::watchLatlonCombined.setValue(latLonCombinedString);
        }
    }
}

QString ObjectPolygonWatch::getData() {
    return storage.getValue();
}

QString ObjectPolygonWatch::getUrl() {
    QString downloadUrl = "";
    if (type1 == PolygonType::mcd) {
        downloadUrl = GlobalVariables::nwsSPCwebsitePrefix + "/products/md/";
    }
    else if (type1 == PolygonType::watch) {
        downloadUrl = GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/";
    }
    else if (type1 == PolygonType::watchTornado) {
        downloadUrl = GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/";
    }
    else if (type1 == PolygonType::mpd) {
        downloadUrl = GlobalVariables::nwsWPCwebsitePrefix + "/metwatch/metwatch_mpd.php";
    }
    return downloadUrl;
}

QString ObjectPolygonWatch::getPrefTokenEnabled() {
    return "RADAR_SHOW_" + getTypeName();
}

QString ObjectPolygonWatch::getPrefTokenStorage() {
    return "SEVERE_DASHBOARD_" + getTypeName();
}

QString ObjectPolygonWatch::getPrefTokenColor() {
    return "RADAR_COLOR_" + getTypeName();
}

QString ObjectPolygonWatch::getPrefTokenNumberList() {
    return getTypeName() + "_NO_LIST";
}

QString ObjectPolygonWatch::getPrefTokenLatLon() {
    return getTypeName() + "_LATLON";
}

QString ObjectPolygonWatch::getTypeName() {
    auto name = namesByEnumId[type1];
    name = name.replace("PolygonType::", "");
    return name;
}

void ObjectPolygonWatch::load() {
    for (auto& data : ObjectPolygonWatch::polygonList) {
        ObjectPolygonWatch::polygonDataByType[data] = new ObjectPolygonWatch(data);
    }
}

QString ObjectPolygonWatch::storeWatchMcdLatLon(QString html) {
    auto coordinates = UtilityString::parseColumn(html, "([0-9]{8}).*?");
    QString value = "";
    for (const auto& coor : coordinates) {
        auto latLon = ObjectPolygonWatch::getLatLonFromString(coor);
        value += latLon.printSpaceSeparated();
    }
    value += ":";
    return value.replace(" :", ":");
}

// 36517623 is 3651 -7623
LatLon ObjectPolygonWatch::getLatLonFromString(QString latLonString) {
    const auto latString = latLonString.left(4);
    const auto lonString = latLonString.right(4);
    auto lat = To::Double(latString);
    auto lon = To::Double(lonString);
    lat /= 100.0;
    lon /= 100.0;
    if (lon < 40.0) {
        lon += 100.0;
    }
    return LatLon(lat, -1.0 * lon);
}

QString ObjectPolygonWatch::getLatLon(QString number) {
    auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/wou" + number + ".html");
    return UtilityString::parseMultiLineLastMatch(html, GlobalVariables::pre2Pattern);
}
