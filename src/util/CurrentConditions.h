// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef CURRENTCONDITIONS_H
#define CURRENTCONDITIONS_H

#include <string>
#include <vector>
#include "objects/LatLon.h"

using std::string;
using std::vector;

class CurrentConditions {
public:
    void process(const LatLon& latLon, int index = 0);
    void formatCurrentConditions();
    static void loadMetarData();
    string getObsFullName() const;
    void timeCheck();
    string summary;
    string temperature;
    string windChill;
    string heatIndex;
    string dewPoint;
    string relativeHumidity;
    string seaLevelPressure;
    string windDirection;
    string windSpeed;
    string windGust;
    string visibility;
    string condition;
    string conditionsTimeString;
    string obsStation;
    vector<string> conditions;
    string data;
    string iconUrl;
    string status;
    string topLine;
    string middleLine;
    string bottomLine;

private:
    static string metarFileName;
    static bool metarSitesInitialized;
    static vector<string> metarSites;
    LatLon latLon;
    string timeStringUtc;
};

#endif  // CURRENTCONDITIONS_H
