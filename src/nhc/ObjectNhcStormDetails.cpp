// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/ObjectNhcStormDetails.h"
#include "nhc/UtilityNhc.h"
#include "util/UtilityIO.h"

ObjectNhcStormDetails::ObjectNhcStormDetails() {
}

ObjectNhcStormDetails::ObjectNhcStormDetails(
    const QString& name,
    const QString& movementDir,
    const QString& movementSpeed,
    const QString& pressure,
    const QString& binNumber,
    const QString& id,
    const QString& lastUpdate,
    const QString& classification,
    const QString& lat,
    const QString& lon,
    const QString& intensity,
    const QString& status) {
    this->name = name;
    this->movementDir = movementDir;
    this->movementSpeed = movementSpeed;
    this->pressure = pressure;
    this->binNumber = binNumber;
    this->id = id;
    this->lastUpdate = lastUpdate;
    this->classification = classification;
    this->lat = lat;
    this->lon = lon;
    this->intensity = intensity;
    this->status = status;
    center = lat + " " + lon;
    const auto modBinNumber = id.left(4).toUpper().replace("AL", "AT");
    baseUrl = "https://www.nhc.noaa.gov/storm_graphics/" + modBinNumber + "/" + id.toUpper();
    //movement = movementDir + " at " + movementSpeed + " mph";

    goesUrl = "https://cdn.star.nesdis.noaa.gov/FLOATER/data/" + id.toUpper() + "/GEOCOLOR/latest.jpg";
    movement = movementDir + " at " + movementSpeed + " mph";
    coneBytes = UtilityIO::downloadAsByteArray(baseUrl + UtilityNhc::urlEnds[0]);
}

QString ObjectNhcStormDetails::getUpdateTime() const {
    auto lastUpdateLocal = lastUpdate;
    lastUpdateLocal = lastUpdateLocal.replace("T", " ");
    lastUpdateLocal = lastUpdateLocal.replace(":00.000Z", "Z");
    return lastUpdateLocal;
}

QString ObjectNhcStormDetails::forTopHeader() const {
    return movement + ", " + pressure + " mb, " + intensity + " mph";
}
