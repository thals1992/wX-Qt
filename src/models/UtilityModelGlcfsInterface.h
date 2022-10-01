// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMODELGLCFSINTERFACE_H
#define UTILITYMODELGLCFSINTERFACE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class UtilityModelGlcfsInterface {
public:
    static const vector<string> sectors;
    static const vector<string> params;
    static const vector<string> labels;
};

#endif  // UTILITYMODELGLCFSINTERFACE_H
