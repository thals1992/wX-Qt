// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/RID.h"

RID::RID() {
}

RID::RID(const QString& name, const LatLon& location) {
    this->name = name;
    this->location = location;
}
