// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RADARUTILITYNWSRADARMOSAIC_H
#define RADARUTILITYNWSRADARMOSAIC_H

#include <string>
#include <unordered_map>
#include <vector>
#include "../objects/LatLon.h"

using std::string;
using std::vector;
using std::unordered_map;

class UtilityNwsRadarMosaic {
public:
    static string getNearest(const LatLon&);
    static string get(const string&);
    static vector<string> getAnimation(const string&, const string&, int);
    static const string baseUrl;
    static const vector<string> sectors;
    static const unordered_map<string, LatLon> cityToLatLon;
};

#endif  // RADARUTILITYNWSRADARMOSAIC_H
