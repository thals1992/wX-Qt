// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/PressureCenter.h"

PressureCenter::PressureCenter() {
}

PressureCenter::PressureCenter(const PressureCenterTypeEnum& centerType, const QString& pressureInMb, float lat, float lon) {
    this->centerType = centerType;
    this->pressureInMb = pressureInMb;
    this->lat = lat;
    this->lon = lon;
}
