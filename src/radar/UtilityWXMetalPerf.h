// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYWXMETALPERF_H
#define UTILITYWXMETALPERF_H

#include "objects/FileStorage.h"
#include "radar/ObjectMetalRadarBuffers.h"
#include "radar/WXMetalNexradLevelData.h"

class UtilityWXMetalPerf {
public:
    static int decode8BitAndGenRadials(ObjectMetalRadarBuffers *, FileStorage *);
    static int genRadials(ObjectMetalRadarBuffers *);
};

#endif  // UTILITYWXMETALPERF_H
