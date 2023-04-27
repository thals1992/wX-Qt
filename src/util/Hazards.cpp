// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/Hazards.h"
#include "util/UtilityIO.h"

Hazards::Hazards() = default;

void Hazards::process(const LatLon& latLon) {
    data = UtilityIO::getHtml("https://api.weather.gov/alerts?point=" + latLon.latStr() + "," + latLon.lonStr() + "&active=1");
}
