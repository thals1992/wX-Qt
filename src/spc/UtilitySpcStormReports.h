// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCUTILITYSPCSTORMREPORTS_H
#define SPCUTILITYSPCSTORMREPORTS_H

#include <string>
#include <vector>
#include "spc/StormReport.h"

using std::string;
using std::vector;

class UtilitySpcStormReports {
public:
    static vector<StormReport> process(const vector<string>&);
};

#endif  // SPCUTILITYSPCSTORMREPORTS_H
