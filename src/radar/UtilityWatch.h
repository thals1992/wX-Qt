// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYWATCH_H
#define UTILITYWATCH_H

#include <QVector>
#include "objects/LatLon.h"
#include "radar/PolygonType.h"
#include "util/ProjectionNumbers.h"

class UtilityWatch {
public:
    static QVector<float> add(const ProjectionNumbers&, PolygonType);
    static QString countString(PolygonType);
    static QString show(LatLon, PolygonType);
};

#endif  // UTILITYWATCH_H
