// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityDownloadNws.h"
#include <string>
#include "common/GlobalVariables.h"
#include "objects/URL.h"
#include "objects/WString.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"

string UtilityDownloadNws::getHourlyData(const LatLon& latLon) {
    const auto pointsData = getLocationPointData(latLon);
    const auto hourlyUrl = UtilityString::parse(pointsData, "\"forecastHourly\": \"(.*?)\"");
    return UtilityIO::getHtml(hourlyUrl);
}

string UtilityDownloadNws::get7DayData(const LatLon& latLon) {
    const auto pointsData = getLocationPointData(latLon);
    const auto forecastUrl = UtilityString::parse(pointsData, "\"forecast\": \"(.*?)\"");
    return UtilityIO::getHtml(forecastUrl);
}

string UtilityDownloadNws::getLocationPointData(const LatLon& latLon) {
    return UtilityIO::getHtml(GlobalVariables::nwsApiUrl + "/points/" + latLon.latStr() + "," + latLon.lonStr());
}

string UtilityDownloadNws::getCap(const string& sector) {
    if (sector == "us") {
        return getHtmlWithXml("https://api.weather.gov/alerts/active?region_type=land");
    } else {
        return getHtmlWithXml("https://api.weather.gov/alerts/active?state=" + WString::toUpper(sector));
    }
}

string UtilityDownloadNws::getHtmlWithXml(const string& url) {
    return URL{url}.getTextXmlAcceptHeader();
}
