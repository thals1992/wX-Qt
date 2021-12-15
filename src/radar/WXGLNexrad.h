// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLNEXRAD_H
#define WXGLNEXRAD_H

#include <cstdint>
#include <QStringList>

class WXGLNexrad {
public:
    static float wxoglDspLegendMax;
    static double getBinSize(int16_t);
    static int getNumberRangeBins(int16_t);
    static bool isProductTdwr(const QString&);
    static const QStringList radarProductList;
    static const QStringList radarProductListTdwr;
};

#endif  // WXGLNEXRAD_H
