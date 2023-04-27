// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/UtilityLocation.h"
#include <algorithm>
#include "common/GlobalArrays.h"
#include "objects/WString.h"
#include "radar/RadarSites.h"
#include "util/SoundingSites.h"
#include "util/Utility.h"
#include "util/UtilityList.h"
#include "util/WfoSites.h"

LatLon UtilityLocation::getSiteLocation(const string& site, OfficeTypeEnum officeType) {
    string x{"0.0"};
    string y{"0.0"};
    if (officeType == OfficeTypeEnum::RadarSite) {
        const auto latLon = getRadarSiteLatLon(WString::toUpper(site));
        x = latLon.latStr();
        y = latLon.lonStr();
    } else if (officeType == OfficeTypeEnum::Wfo) {
        const auto latLon = getWfoSiteLatLon(WString::toUpper(site));
        x = latLon.latStr();
        y = latLon.lonStr();
    } else if (officeType == OfficeTypeEnum::Sounding) {
        const auto latLon = getSoundingSiteLatLon(WString::toUpper(site));
        x = latLon.latStr();
        y = latLon.lonStr();
    }
    return {x, y};
}

vector<RID> UtilityLocation::getNearestRadarSites(const LatLon& latLon, int count, bool includeTdwr) {
    vector<RID> radarSites;
    for (const auto& radar : GlobalArrays::nexradRadars) {
        const auto labels = WString::split(radar, ":");
        radarSites.emplace_back(labels[0], getSiteLocation(labels[0], OfficeTypeEnum::RadarSite), latLon.dist(getSiteLocation(labels[0], OfficeTypeEnum::RadarSite)));
    }
    if (includeTdwr) {
        for (const auto& radar : GlobalArrays::tdwrRadars) {
            const auto labels = WString::split(radar, ":");
            radarSites.emplace_back(labels[0], getSiteLocation(labels[0], OfficeTypeEnum::RadarSite), latLon.dist(getSiteLocation(labels[0], OfficeTypeEnum::RadarSite)));
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
            auto latLon = getWfoSiteLatLon(labelArr[0]);
            sites.emplace_back(labelArr[0], latLon, location.dist(latLon));
        } else {
            auto latLon = getRadarSiteLatLon(labelArr[0]);
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

string UtilityLocation::getRadarSiteName(const string& radarSite) {
    return RadarSites::radarIdToName.at(radarSite);
}

LatLon UtilityLocation::getRadarSiteLatLon(const string& radarSite) {
    return {RadarSites::radarSiteToLat.at(radarSite), "-" + RadarSites::radarSiteToLon.at(radarSite)};
}

string UtilityLocation::getRadarSiteX(const string& radarSite) {
    return RadarSites::radarSiteToLat.at(radarSite);
}

string UtilityLocation::getRadarSiteY(const string& radarSite) {
    return RadarSites::radarSiteToLon.at(radarSite);
}

LatLon UtilityLocation::getWfoSiteLatLon(const string& wfo) {
    return {WfoSites::wfoSiteToLat.at(wfo), WfoSites::wfoSiteToLon.at(wfo)};
}

LatLon UtilityLocation::getSoundingSiteLatLon(const string& wfo) {
    return {SoundingSites::soundingSiteToLat.at(wfo), "-" + SoundingSites::soundingSiteToLon.at(wfo)};
}

string UtilityLocation::getNearest(const LatLon& latLon, const unordered_map<string, LatLon>& sectorToLatLon) {
    vector<RID> sites;
    for (const auto& m : sectorToLatLon) {
        sites.emplace_back(m.first, m.second, latLon.dist(m.second));
    }
    std::sort(
        sites.begin(),
        sites.end(),
        [] (const auto& s1, const auto& s2) { return s1.distance < s2.distance; });
    return sites[0].name;
}
