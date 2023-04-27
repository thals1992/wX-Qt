// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLNEXRAD_H
#define WXGLNEXRAD_H

#include <cstdint>
#include <string>
#include <vector>

using std::string;
using std::vector;

class NexradUtil {
public:
    static double getBinSize(uint16_t);
    static int getNumberRangeBins(uint16_t);
    static bool isProductTdwr(const string&);
    static bool isRadarTimeOld(int);
    static bool isVtecCurrent(const string&);
    static double wxoglDspLegendMax;
    static const vector<string> radarProductList;
    static const vector<string> radarProductListTdwr;
};

#endif  // WXGLNEXRAD_H
