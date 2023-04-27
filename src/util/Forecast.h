// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTFORECAST_H
#define OBJECTFORECAST_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Forecast {
public:
    Forecast(const string&, const string&, const string&, const string&, const string&, const string&, const string&);
    string name;
    string temperature;
    string windSpeed;
    string windDirection;
    string icon;
    string shortForecast;
    string detailedForecast;
};

#endif  // OBJECTFORECAST_H
