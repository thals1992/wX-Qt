// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/UtilityLocation.h"
#include <algorithm>
#include "common/GlobalArrays.h"
#include "util/Utility.h"
#include "util/UtilityList.h"

LatLon UtilityLocation::getSiteLocation(const QString& site, const QString& officeType) {
    QString x = "";
    QString y = "";
    if (officeType == "RID") {
        const auto latLon = Utility::getRadarSiteLatLon(site.toUpper());
        x = latLon.latString;
        y = latLon.lonString;
    } else if (officeType == "NWS") {
        const auto latLon = Utility::getWfoSiteLatLon(site.toUpper());
        x = latLon.latString;
        y = latLon.lonString;
    } else if (officeType == "SND") {
        const auto latLon = Utility::getSoundingSiteLatLon(site.toUpper());
        x = latLon.latString;
        y = latLon.lonString;
    } else {
        x = "0.0";
        y = "-0.0";
    }
    return LatLon(x, y);
}

QVector<RID> UtilityLocation::getNearestRadarSites(const LatLon& latLon, int cnt, bool includeTdwr) {
    QVector<RID> radarSites;
    for (const auto& radar : GlobalArrays::nexradRadars) {
        const auto labels = radar.split(":");
        radarSites.push_back(RID(labels[0], getSiteLocation(labels[0])));
    }
    if (includeTdwr) {
        for (const auto& radar : GlobalArrays::tdwrRadars) {
            const auto labels = radar.split(" ");
            radarSites.push_back(RID(labels[0], getSiteLocation(labels[0])));
        }
    }
    int index = 0;
    for (const auto& radar : radarSites) {
        const auto currentDistance = latLon.dist(radar.location);
        radarSites[index].distance = currentDistance;
        index += 1;
    }
    std::sort(radarSites.begin(), radarSites.end(), compareSites);
    // Qvector::mid -- Returns a sub-vector which contains elements from this vector, starting at position pos.
    // If length is -1 (the default), all elements after pos are included; otherwise length elements (or all remaining
    // elements if there are less than length elements) are included. https://doc.qt.io/qt-5/qvector.html#mid
    return radarSites.mid(0, cnt);
}

QString UtilityLocation::getNearestOffice(const QString& officeType, const LatLon& location) {
    QStringList officeArray;
    if (officeType == "WFO") {
        officeArray = GlobalArrays::wfos;
    } else {
        officeArray = GlobalArrays::nexradRadars; // was radars()
    }
    QVector<RID> sites;
    for (const auto& office : officeArray) {
        const auto labelArr = office.split(":");
        if (officeType == "WFO") {
            auto latLon = Utility::getWfoSiteLatLon(labelArr[0]);
            sites.push_back(RID(labelArr[0], latLon));
        } else {
            auto latLon = Utility::getRadarSiteLatLon(labelArr[0]);
            sites.push_back(RID(labelArr[0], latLon));
        }
    }
    auto shortestDistance = 30000.00;
    auto bestIndex = -1;
    for (auto index : UtilityList::range(sites.size())) {
        const auto currentDistance = location.dist(sites[index].location);
        if (currentDistance < shortestDistance) {
            shortestDistance = currentDistance;
            bestIndex = index;
        }
    }
    return sites[bestIndex].name;
}

// latLon input is all positive numbers
LatLon UtilityLocation::getCenterOfPolygon(const QVector<LatLon>& latLons) {
    double x = 0.0;
    double y = 0.0;
    for (const auto& latLon : latLons) {
        x += latLon.lat;
        y += latLon.lon;
    }
    const auto totalPoints = latLons.size();
    x /= static_cast<float>(totalPoints);
    y /= static_cast<float>(totalPoints);
    return LatLon(x, -1.0 * y);
}

bool UtilityLocation::compareSites(const RID &s1, const RID &s2) {
    return s1.distance < s2.distance;
}
