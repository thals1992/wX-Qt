// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTHAZARDS_H
#define OBJECTHAZARDS_H

#include <string>
#include "objects/LatLon.h"

using std::string;

class Hazards {
public:
    Hazards();
    void process(const LatLon& latLon);
    string data;
};

#endif  // OBJECTHAZARDS_H
