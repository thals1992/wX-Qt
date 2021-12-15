// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYCITIESEXTENDED_H
#define UTILITYCITIESEXTENDED_H

#include <QVector>
#include "radar/CityExt.h"

class UtilityCitiesExtended {
public:
    static bool initialized;
    static QVector<CityExt> cities;
    static void create();
};

#endif  // UTILITYCITIESEXTENDED_H
