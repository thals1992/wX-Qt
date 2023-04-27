// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SOUNDINGSITES_H
#define SOUNDINGSITES_H

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class SoundingSites {
public:
    static const unordered_map<string, string> soundingSiteToLat;
    static const unordered_map<string, string> soundingSiteToLon;
};

#endif  // SOUNDINGSITES_H
