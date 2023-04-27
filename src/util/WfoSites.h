// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WFOSITES_H
#define WFOSITES_H

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class WfoSites {
public:
    static const unordered_map<string, string> wfoSiteToLat;
    static const unordered_map<string, string> wfoSiteToLon;
};

#endif  // WFOSITES_H
