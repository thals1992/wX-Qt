// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYCOUNTYLABELS_H
#define UTILITYCOUNTYLABELS_H

#include <QStringList>
#include <QVector>
#include "objects/LatLon.h"

class UtilityCountyLabels {
public:
    static bool initialized;
    static QStringList names;
    static QVector<LatLon> location;
    static void create();
};

#endif  // UTILITYCOUNTYLABELS_H
