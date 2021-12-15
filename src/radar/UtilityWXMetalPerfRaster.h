// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYWXMETALPERFRASTER_H
#define UTILITYWXMETALPERFRASTER_H

#include "radar/WXMetalNexradLevelData.h"

class UtilityWXMetalPerfRaster {
public:
    static int generate(WXMetalNexradLevelData *);
};

#endif  // UTILITYWXMETALPERFRASTER_H
