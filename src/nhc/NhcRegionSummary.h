// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTNHCREGIONSUMMARY_H
#define OBJECTNHCREGIONSUMMARY_H

#include <string>
#include <vector>
#include "nhc/NhcOceanEnum.h"

using std::string;
using std::vector;

class NhcRegionSummary {
public:
    explicit NhcRegionSummary(const NhcOceanEnum&);
    vector<string> urls;
    vector<string> titles;
    string baseUrl;
};

#endif  // OBJECTNHCREGIONSUMMARY_H
