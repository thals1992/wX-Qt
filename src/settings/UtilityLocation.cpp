// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/UtilityLocation.h"
#include <algorithm>
#include "common/GlobalArrays.h"
#include "objects/WString.h"
#include "util/Utility.h"
#include "util/UtilityList.h"

LatLon UtilityLocation::getSiteLocation(const string& site, const string& officeType) {
    string x{"0.0"};
    string y{"0.0"};
    if (officeType == "RID") {
        const auto latLon = Utility::getRadarSiteLatLon(WString::toUpper(site));
        x = latLon.latStr();
        y = latLon.lonStr();
    } else if (officeType == "NWS") {
        const auto latLon = Utility::getWfoSiteLatLon(WString::toUpper(site));
        x = latLon.latStr();
        y = latLon.lonStr();
    } else if (officeType == "SND") {
        const auto latLon = Utility::getSoundingSiteLatLon(WString::toUpper(site));
        x = latLon.latStr();
        y = latLon.lonStr();
    }
    return {x, y};
}

vector<RID> UtilityLocation::getNearestRadarSites(const LatLon& latLon, int count, bool includeTdwr) {
    vector<RID> radarSites;
    for (const auto& radar : GlobalArrays::nexradRadars) {
        const auto labels = WString::split(radar, ":");
        radarSites.emplace_back(labels[0], getSiteLocation(labels[0]), latLon.dist(getSiteLocation(labels[0])));
    }
    if (includeTdwr) {
        for (const auto& radar : GlobalArrays::tdwrRadars) {
            const auto labels = WString::split(radar, " ");
            radarSites.emplace_back(labels[0], getSiteLocation(labels[0]), latLon.dist(getSiteLocation(labels[0])));
        }
    }
    std::sort(
        radarSites.begin(),
        radarSites.end(),
        [] (const RID &s1, const RID &s2) { return s1.distance < s2.distance; });
    // QVector::mid -- Returns a sub-vector which contains elements from this vector, starting at position pos.
    // If length is -1 (the default), all elements after pos are included; otherwise length elements (or all remaining
    // elements if there are less than length elements) are included. https://doc.qt.io/qt-5/qvector.html#mid
    // return radarSites.mid(0, cnt);
    return {radarSites.begin(), radarSites.begin() + count};
}

string UtilityLocation::getNearestOffice(const string& officeType, const LatLon& location) {
    vector<string> officeArray;
    if (officeType == "WFO") {
        officeArray = GlobalArrays::wfos;
    } else {
        officeArray = GlobalArrays::nexradRadars;  // was radars()
    }
    vector<RID> sites;
    for (const auto& office : officeArray) {
        const auto labelArr = WString::split(office, ":");
        if (officeType == "WFO") {
            auto latLon = Utility::getWfoSiteLatLon(labelArr[0]);
            sites.emplace_back(labelArr[0], latLon, location.dist(latLon));
        } else {
            auto latLon = Utility::getRadarSiteLatLon(labelArr[0]);
            sites.emplace_back(labelArr[0], latLon, location.dist(latLon));
        }
    }
    std::sort(
        sites.begin(),
        sites.end(),
        [] (const RID &s1, const RID &s2) { return s1.distance < s2.distance; });
    return sites[0].name;
}

// latLon input is all positive numbers
LatLon UtilityLocation::getCenterOfPolygon(const vector<LatLon>& latLons) {
    auto x = 0.0;
    auto y = 0.0;
    for (const auto& latLon : latLons) {
        x += latLon.lat();
        y += latLon.lon();
    }
    auto totalPoints = static_cast<double>(latLons.size());
    x /= totalPoints;
    y /= totalPoints;
    return {x, -1.0 * y};
}
