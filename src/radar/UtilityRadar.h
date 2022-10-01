// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYRADAR_H
#define UTILITYRADAR_H

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class UtilityRadar {
public:
    static const unordered_map<string, string> radarIdToName;
    static const unordered_map<string, string> wfoSiteToLat;
    static const unordered_map<string, string> wfoSiteToLon;
    static const unordered_map<string, string> radarSiteToLat;
    static const unordered_map<string, string> radarSiteToLon;
    static const unordered_map<string, string> soundingSiteToLat;
    static const unordered_map<string, string> soundingSiteToLon;
};

#endif  // UTILITYRADAR_H
