// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/ProjectionNumbers.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityMath.h"

ProjectionNumbers::ProjectionNumbers() {
}

ProjectionNumbers::ProjectionNumbers(const QString& radarSite) {
    this->radarSite = radarSite;
    scale = 190.00;
    xCenter = 0;
    yCenter = 0;
    lat = Utility::getRadarSiteX(radarSite);
    lon = Utility::getRadarSiteY(radarSite);
    oneDegreeScaleFactor = UtilityMath::pixPerDegreeLon(To::Float(lat), scale);
}

float ProjectionNumbers::xDbl() const {
    return To::Float(lat);
}

float ProjectionNumbers::yDbl() const {
    return To::Float(lon);
}

float ProjectionNumbers::getOneDegreeScaleFactor() const {
    return oneDegreeScaleFactor;
}
