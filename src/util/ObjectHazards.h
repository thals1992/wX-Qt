// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTHAZARDS_H
#define OBJECTHAZARDS_H

#include "objects/LatLon.h"

class ObjectHazards {
public:
    ObjectHazards();
    explicit ObjectHazards(const LatLon&);
    QString data;

private:
    LatLon latLon;
};

#endif  // OBJECTHAZARDS_H
