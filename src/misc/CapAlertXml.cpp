// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "common/GlobalVariables.h"
#include "misc/CapAlertXml.h"
#include "objects/LatLon.h"
#include "objects/WString.h"
#include "settings/UtilityLocation.h"
#include "util/To.h"
#include "util/UtilityString.h"

CapAlertXml::CapAlertXml(const string& s) {
    url = UtilityString::parse(s, "<id>(.*?)</id>");
    title = UtilityString::parse(s, "<title>(.*?)</title>");
    summary = UtilityString::parse(s, "<summary>(.*?)</summary>");
    instructions = UtilityString::parse(s, "</description>.*?<instruction>(.*?)</instruction>.*?<areaDesc>");
    area = UtilityString::parse(s, "<cap:areaDesc>(.*?)</cap:areaDesc>");
    area = WString::replace(area, "&apos;", "'");
    effective = UtilityString::parse(s, "<cap:effective>(.*?)</cap:effective>");
    expires = UtilityString::parse(s, "<cap:expires>(.*?)</cap:expires>");
    event = UtilityString::parse(s, "<cap:event>(.*?)</cap:event>");
//    vtec = UtilityString::parse(s, "<valueName>VTEC</valueName>.*?<value>(.*?)</value>");
//    zones = UtilityString::parse(s, "<valueName>UGC</valueName>.*?<value>(.*?)</value>");
    polygon = UtilityString::parse(s, "<cap:polygon>(.*?)</cap:polygon>");
    text = title;
    text += GlobalVariables::newline;
    text += "Counties: ";
    text += area;
    text += GlobalVariables::newline;
    text += summary;
    text += GlobalVariables::newline;
    text += instructions;
    text += GlobalVariables::newline;
    summary = WString::replace(summary, "<br>\\*", "<br><br>*");
    points = WString::split(polygon, " ");
}

string CapAlertXml::getClosestRadar() const {
    if (points.size() > 2) {
        const auto lat = To::Double(WString::split(points[0], ",")[0]);
        const auto lon = To::Double(WString::split(points[0], ",")[1]);
        const auto latLon = LatLon{lat, lon};
        const auto radarSites = UtilityLocation::getNearestRadarSites(latLon, 1, false);
        return radarSites[0].name;
    } else {
        return "";
    }
}
