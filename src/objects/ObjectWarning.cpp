// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ObjectWarning.h"
#include "common/GlobalVariables.h"
#include "settings/UtilityLocation.h"
#include "util/Utility.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"
#include "util/UtilityTime.h"

ObjectWarning::ObjectWarning() {
}

ObjectWarning::ObjectWarning(
    QString url,
    QString title,
    QString area,
    QString effective,
    QString expires,
    QString event,
    QString sender,
    QString polygon,
    QString vtec,
    QString geometry
) {
    this->url = url;
    // detailed desc
    this->title = title;
    this->area = area;

    this->effective = effective;
    this->effective = this->effective.replace("T", " ");
    this->effective = UtilityString::replaceRegex(this->effective, ":00-0[0-9]:00", "");

    this->expires = expires;
    this->expires = this->expires.replace("T", " ");
    this->expires = UtilityString::replaceRegex(this->expires, ":00-0[0-9]:00", "");

    this->event = event;
    this->sender = sender;
    this->polygon = polygon;
    this->vtec = vtec;
    this->geometry = geometry;

    this->isCurrent = UtilityTime::isVtecCurrent(this->vtec);
    if (vtec.startsWith("O.EXP") || vtec.startsWith("O.CAN")) {
        this->isCurrent = false;
    }
}

QVector<ObjectWarning> ObjectWarning::parseJson(QString htmlF) {
    QVector<ObjectWarning> warnings;
    QString html = htmlF;
    html = html.replace("\"geometry\": null,", "\"geometry\": null, \"coordinates\":[[]]}");

    const auto urlList = UtilityString::parseColumn(html, "\"id\": \"(https://api.weather.gov/alerts/urn.*?)\"");
    const auto titleList = UtilityString::parseColumn(html, "\"description\": \"(.*?)\"");
    const auto areaDescList = UtilityString::parseColumn(html, "\"areaDesc\": \"(.*?)\"");
    const auto effectiveList = UtilityString::parseColumn(html, "\"effective\": \"(.*?)\"");
    const auto expiresList = UtilityString::parseColumn(html, "\"expires\": \"(.*?)\"");
    const auto eventList = UtilityString::parseColumn(html, "\"event\": \"(.*?)\"");
    const auto senderNameList = UtilityString::parseColumn(html, "\"senderName\": \"(.*?)\"");
    const auto geometryList = UtilityString::parseColumn(html, "\"geometry\": (.*?),");
    auto data = html;
    data = data.replace("\n", "");
    data = data.replace(" ", "");
    const auto listOfPolygonRaw = UtilityString::parseColumn(data, GlobalVariables::warningLatLonPattern);
    const auto vtecs = UtilityString::parseColumn(html, GlobalVariables::vtecPattern);
    for (auto index : UtilityList::range(urlList.size())) {
        warnings.push_back(ObjectWarning(
            Utility::safeGet(urlList, index),
            Utility::safeGet(titleList, index),
            Utility::safeGet(areaDescList, index),
            Utility::safeGet(effectiveList, index),
            Utility::safeGet(expiresList, index),
            Utility::safeGet(eventList, index),
            Utility::safeGet(senderNameList, index),
            Utility::safeGet(listOfPolygonRaw, index),
            Utility::safeGet(vtecs, index),
            Utility::safeGet(geometryList, index)
        ));
    }
    return warnings;
}

QString ObjectWarning::getClosestRadar() const {
    auto listOfPolygonRawLocal = polygon;
    const auto data = listOfPolygonRawLocal.replace("[", "").replace("]", "").replace(",", " ").replace("-", "");
    const auto points = data.split(" ");
    if (points.size() > 2) {
        const auto lat = points[1];
        const auto lon = "-" + points[0];
        const auto radarSites = UtilityLocation::getNearestRadarSites(LatLon(lat, lon), 1, false);
        if (radarSites.size() == 0) {
            return "";
        } else {
            return radarSites[0].name;
        }
    } else {
        return "";
    }
}

QString ObjectWarning::getUrl() const {
    return url;
}

QVector<LatLon> ObjectWarning::getPolygonAsLatLons(int mult) const {
    auto polygonTmp = polygon;
    polygonTmp = polygonTmp.replace("[", "");
    polygonTmp = polygonTmp.replace("]", "");
    polygonTmp = polygonTmp.replace(",", " ");
    auto latLons = LatLon::parseStringToLatLons(polygonTmp, mult, true);
    return latLons;
}

/*



SPS could have
    "geometry": null,

    or

                "geometry": {
                "type": "Polygon",
                "coordinates": [
                    [
                        [
                            -84.2099999,
                            45.619999999999997
                        ],
                        [
                            -84.25,
                            45.619999999999997
                        ],
                        [
                            -84.25,
                            45.579999999999998
                        ],
                        [
                            -84.489999999999995,
                            45.32
                        ],
                        [
                            -84.689999999999998,
                            45.380000000000003
                        ],
                        [
                            -84.469999999999999,
                            45.720000000000006
                        ],
                        [
                            -84.359999999999999,
                            45.710000000000008
                        ],
                        [
                            -84.370000000000005,
                            45.70000000000001
                        ],
                        [
                            -84.310000000000002,
                            45.70000000000001
                        ],
                        [
                            -84.180000000000007,
                            45.65999990000001
                        ],
                        [
                            -84.2099999,
                            45.619999999999997
                        ]
                    ]
                ]
            },

*/
