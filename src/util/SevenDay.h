// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTSEVENDAY_H
#define OBJECTSEVENDAY_H

#include <string>
#include <vector>
#include "objects/LatLon.h"

using std::string;
using std::vector;

class SevenDay {
public:
    void process(const LatLon&);
    vector<string> icons;
    vector<string> shortForecasts;
    vector<string> detailedForecasts;
};

#endif  // OBJECTSEVENDAY_H
