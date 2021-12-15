// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/ObjectHazards.h"
#include "util/UtilityIO.h"

ObjectHazards::ObjectHazards() {
}

ObjectHazards::ObjectHazards(const LatLon& latLon) {
    this->latLon = latLon;
    const auto url = "https://api.weather.gov/alerts?point=" + latLon.latString + "," + latLon.lonString + "&active=1";
    data = UtilityIO::getHtml(url);
}
