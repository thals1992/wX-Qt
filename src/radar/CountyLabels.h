// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYCOUNTYLABELS_H
#define UTILITYCOUNTYLABELS_H

#include <string>
#include <vector>
#include "objects/LatLon.h"

using std::string;
using std::vector;

class CountyLabels {
public:
    static void create();
    static bool initialized;
    static vector<string> names;
    static vector<LatLon> location;
};

#endif  // UTILITYCOUNTYLABELS_H
