// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RID_H
#define RID_H

#include <string>
#include "objects/LatLon.h"

using std::string;

class RID {
public:
    RID(const string&, const LatLon&, double);
    string name;
    LatLon location;
    double distance;
};

#endif  // RID_H
