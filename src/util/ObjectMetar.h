// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTMETAR_H
#define OBJECTMETAR_H

#include <string>
#include <vector>
#include "radar/RID.h"

using std::string;
using std::vector;

class ObjectMetar {
public:
    explicit ObjectMetar(const LatLon&, int index = 0);
    void process();
    static string changePressureUnits(const string&);
    static string changeDegreeUnits(const string&);
    static string decodeIconFromMetar(const string&, const RID&);
    // LatLon location;
    RID obsClosest;
    string condition;
    string temperature;
    string dewPoint;
    string windDirection;
    string windSpeed;
    string windGust;
    string seaLevelPressure;
    string visibility;
    string relativeHumidity;
    string windChill;
    string heatIndex;
    string conditionsTimeString;
    string timeStringUtc;
    string icon;
    string metarData;
    vector<string> metarDataList;

private:
    string metarSkyCondition;
    string metarWeatherCondition;
    bool decodeIcon{true};
};

#endif  // OBJECTMETAR_H
