// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef PRESSURECENTER_H
#define PRESSURECENTER_H

#include <QString>
#include "radar/PressureCenterTypeEnum.h"

class PressureCenter {
public:
    PressureCenter();
    PressureCenter(const PressureCenterTypeEnum&, const QString&, float, float);
    PressureCenterTypeEnum centerType;
    QString pressureInMb;
    float lat;
    float lon;
};

#endif  // PRESSURECENTER_H
