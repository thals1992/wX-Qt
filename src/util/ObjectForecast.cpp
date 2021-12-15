// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/ObjectForecast.h"

ObjectForecast::ObjectForecast() {
}

ObjectForecast::ObjectForecast(
    const QString& name,
    const QString& temperature,
    const QString& windSpeed,
    const QString& windDirection,
    const QString& icon,
    const QString& shortForecast,
    const QString& detailedForecast
) {
    this->name = name;
    this->temperature = temperature;
    this->windSpeed = windSpeed;
    this->windDirection = windDirection;
    this->icon = icon;
    this->shortForecast = shortForecast;
    this->detailedForecast = detailedForecast;
}
