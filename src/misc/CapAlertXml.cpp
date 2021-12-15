// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "common/GlobalVariables.h"
#include <QVector>
#include "misc/CapAlertXml.h"
#include "objects/LatLon.h"
#include "settings/UtilityLocation.h"
#include "util/To.h"
#include "util/UtilityString.h"

CapAlertXml::CapAlertXml() {
}

CapAlertXml::CapAlertXml(const QString& eventText) {
    url = UtilityString::parse(eventText, "<id>(.*?)</id>");
    title = UtilityString::parse(eventText, "<title>(.*?)</title>");
    summary = UtilityString::parse(eventText, "<summary>(.*?)</summary>");
    instructions = UtilityString::parse(eventText, "</description>.*?<instruction>(.*?)</instruction>.*?<areaDesc>");
    area = UtilityString::parse(eventText, "<cap:areaDesc>(.*?)</cap:areaDesc>");
    area = area.replace("&apos;", "'");
    effective = UtilityString::parse(eventText, "<cap:effective>(.*?)</cap:effective>");
    expires = UtilityString::parse(eventText, "<cap:expires>(.*?)</cap:expires>");
    event = UtilityString::parse(eventText, "<cap:event>(.*?)</cap:event>");
    vtec = UtilityString::parse(eventText, "<valueName>VTEC</valueName>.*?<value>(.*?)</value>");
    zones = UtilityString::parse(eventText, "<valueName>UGC</valueName>.*?<value>(.*?)</value>");
    polygon = UtilityString::parse(eventText, "<cap:polygon>(.*?)</cap:polygon>");
    text = title;
    text += GlobalVariables::newline;
    text += "Counties: ";
    text += area;
    text += GlobalVariables::newline;
    text += summary;
    text += GlobalVariables::newline;
    text += instructions;
    text += GlobalVariables::newline;
    summary = summary.replace("<br>\\*", "<br><br>*");
    points = polygon.split(" ");
}

QString CapAlertXml::getClosestRadar() const {
    if (points.size() > 2) {
        auto lat = To::Float(points[0].split(",")[0]);
        auto lon = To::Float(points[0].split(",")[1]);
        auto latLon = LatLon(lat, lon);
        auto radarSites = UtilityLocation::getNearestRadarSites(latLon, 1, false);
        if (radarSites.size() == 0) {
            return "";
        } else {
            return radarSites[0].name;
        }
    } else {
        return "";
    }
}
