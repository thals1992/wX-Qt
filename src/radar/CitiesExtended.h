// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYCITIESEXTENDED_H
#define UTILITYCITIESEXTENDED_H

#include <vector>
#include "radar/CityExt.h"

using std::vector;

class CitiesExtended {
public:
    static void create();
    static bool initialized;
    static vector<CityExt> cities;
};

#endif  // UTILITYCITIESEXTENDED_H
