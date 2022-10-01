// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/PressureCenter.h"

PressureCenter::PressureCenter(const PressureCenterTypeEnum& centerType, const string& pressureInMb, float lat, float lon)
    : centerType{ centerType }
    , pressureInMb{ pressureInMb }
    , lat{ lat }
    , lon{ lon }
{}
