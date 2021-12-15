// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/CityExt.h"

CityExt::CityExt() {
}

CityExt::CityExt(const QString& name, float latitude, float longitude) {
    this->name = name;
    this->latitude = latitude;
    this->longitude = longitude;
}
