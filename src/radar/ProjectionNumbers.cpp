// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/ProjectionNumbers.h"
#include "settings/Location.h"
#include "settings/UtilityLocation.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityMath.h"

ProjectionNumbers::ProjectionNumbers() {
    setRadarSite(Location::radarSite());
}

void ProjectionNumbers::setRadarSite(const string& radarSite) {
    this->radarSite = radarSite;
    scale = 190.00;
    latString = UtilityLocation::getRadarSiteX(radarSite);
    lonString = UtilityLocation::getRadarSiteY(radarSite);
    oneDegreeScaleFactor = UtilityMath::pixPerDegreeLon(To::Double(latString), scale);
}

double ProjectionNumbers::x() const {
    return To::Double(latString);
}

double ProjectionNumbers::y() const {
    return To::Double(lonString);
}

double ProjectionNumbers::getOneDegreeScaleFactor() const {
    return oneDegreeScaleFactor;
}

string ProjectionNumbers::getRadarSite() const {
    return radarSite;
}
