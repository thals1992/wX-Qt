// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/RID.h"

RID::RID(const string& name, const LatLon& location, double distance)
    : name{ name }
    , location{ location }
    , distance{ distance }
{}
