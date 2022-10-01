// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/ObjectHazards.h"
#include "util/UtilityIO.h"

ObjectHazards::ObjectHazards() = default;

void ObjectHazards::process(const LatLon& latLon) {
    data = UtilityIO::getHtml("https://api.weather.gov/alerts?point=" + latLon.latStr() + "," + latLon.lonStr() + "&active=1");
}
