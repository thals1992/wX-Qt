// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/Forecast.h"

Forecast::Forecast(
    const string& name,
    const string& temperature,
    const string& windSpeed,
    const string& windDirection,
    const string& icon,
    const string& shortForecast,
    const string& detailedForecast
)
    : name{ name }
    , temperature{ temperature }
    , windSpeed{ windSpeed }
    , windDirection{ windDirection }
    , icon{ icon }
    , shortForecast{ shortForecast }
    , detailedForecast{ detailedForecast }
{}
