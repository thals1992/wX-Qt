// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYWXMETALPERF_H
#define UTILITYWXMETALPERF_H

#include "radar/ObjectMetalRadarBuffers.h"
#include "radar/WXMetalNexradLevelData.h"

class UtilityWXMetalPerf {
public:
    static int decode8BitAndGenRadials(ObjectMetalRadarBuffers *, WXMetalNexradLevelData *);
    static int genRadials(ObjectMetalRadarBuffers *, WXMetalNexradLevelData *);
};

#endif  // UTILITYWXMETALPERF_H
