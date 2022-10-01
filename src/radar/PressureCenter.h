// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef PRESSURECENTER_H
#define PRESSURECENTER_H

#include <string>
#include "radar/PressureCenterTypeEnum.h"

using std::string;

class PressureCenter {
public:
    PressureCenter(const PressureCenterTypeEnum&, const string&, float, float);
    PressureCenterTypeEnum centerType;
    string pressureInMb;
    float lat;
    float lon;
};

#endif  // PRESSURECENTER_H
