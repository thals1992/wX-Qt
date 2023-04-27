// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ObjectWarning.h"
#include "common/GlobalVariables.h"
#include "objects/WString.h"
#include "radar/NexradUtil.h"
#include "settings/UtilityLocation.h"
#include "util/Utility.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

ObjectWarning::ObjectWarning(
    const string& url,
    const string& title,
    const string& area,
    const string& effective,
    const string& expires,
    const string& event,
    const string& sender,
    const string& polygon,
    const string& vtec
)
    : url{ url }
    , title{ title }
    , area{ area }
    , effective{ effective }
    , expires{ expires }
    , event{ event }
    , sender{ sender }
    , polygon{ polygon }
    , vtec{ vtec }
    , isCurrent{ NexradUtil::isVtecCurrent(this->vtec) }
{
    this->effective = WString::replace(this->effective, "T", " ");
    this->effective = UtilityString::replaceRegex1(this->effective, ":00-0[0-9]:00", "");
    this->expires = WString::replace(this->expires, "T", " ");
    this->expires = UtilityString::replaceRegex1(this->expires, ":00-0[0-9]:00", "");
    if (WString::startsWith(vtec, "O.EXP") || WString::startsWith(vtec, "O.CAN")) {
        this->isCurrent = false;
    }
}

vector<ObjectWarning> ObjectWarning::parseJson(const string& htmlF) {
    vector<ObjectWarning> warnings;
    const auto html = WString::replace(htmlF, "\"geometry\": null,", "\"geometry\": null, \"coordinates\":[[]]}");
    const auto urlList = UtilityString::parseColumn(html, "\"id\": \"(https://api.weather.gov/alerts/urn.*?)\"");
    const auto titleList = UtilityString::parseColumn(html, "\"description\": \"(.*?)\"");
    const auto areaDescList = UtilityString::parseColumn(html, "\"areaDesc\": \"(.*?)\"");
    const auto effectiveList = UtilityString::parseColumn(html, "\"effective\": \"(.*?)\"");
    const auto expiresList = UtilityString::parseColumn(html, "\"expires\": \"(.*?)\"");
    const auto eventList = UtilityString::parseColumn(html, "\"event\": \"(.*?)\"");
    const auto senderNameList = UtilityString::parseColumn(html, "\"senderName\": \"(.*?)\"");
//    const auto geometryList = UtilityString::parseColumn(html, "\"geometry\": (.*?),");
    // auto data = html;
    // data = data.replace("\n", "");
    // data = data.replace(" ", "");
    auto data = html;
    data = WString::replace(data, "\n", "");
    data = WString::replace(data, " ", "");
    const auto listOfPolygonRaw = UtilityString::parseColumn(data, GlobalVariables::warningLatLonPattern);
    const auto vtecs = UtilityString::parseColumn(html, GlobalVariables::vtecPattern);
    for (auto index : range(urlList.size())) {
        warnings.emplace_back(
            Utility::safeGet(urlList, index),
            Utility::safeGet(titleList, index),
            Utility::safeGet(areaDescList, index),
            Utility::safeGet(effectiveList, index),
            Utility::safeGet(expiresList, index),
            Utility::safeGet(eventList, index),
            Utility::safeGet(senderNameList, index),
            Utility::safeGet(listOfPolygonRaw, index),
            Utility::safeGet(vtecs, index));
    }
    return warnings;
}

string ObjectWarning::getClosestRadar() const {
    auto data = WString::replace(polygon, "[", "");
    data = WString::replace(data, "]", "");
    data = WString::replace(data, ",", " ");
    data = WString::replace(data, "-", "");
    auto points = WString::split(data, " ");
    if (points.size() > 2) {
        const auto lat = points[1];
        const auto lon = "-" + points[0];
        const auto radarSites = UtilityLocation::getNearestRadarSites(LatLon(lat, lon), 1, false);
        if (radarSites.empty()) {
            return "";
        } else {
            return radarSites[0].name;
        }
    } else {
        return "";
    }
}

string ObjectWarning::getUrl() const {
    return url;
}

vector<LatLon> ObjectWarning::getPolygonAsLatLons(int multiplier) const {
    auto polygonTmp = WString::replace(polygon, "[", "");
    polygonTmp = WString::replace(polygonTmp, "]", "");
    polygonTmp = WString::replace(polygonTmp, ",", " ");
    return LatLon::parseStringToLatLons(polygonTmp, multiplier, true);
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
