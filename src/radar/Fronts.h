// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef FRONTS_H
#define FRONTS_H

#include <QColor>
#include <QLineF>
#include <QVector>
#include "objects/LatLon.h"
#include "radar/FrontTypeEnum.h"
#include "util/ProjectionNumbers.h"

class Fronts {
public:
    Fronts();
    explicit Fronts(FrontTypeEnum);
    void translate(const ProjectionNumbers&);
    FrontTypeEnum frontType;
    QVector<LatLon> coordinates;
    QVector<QLineF> qLines;
    QColor penColor;
};

#endif  // FRONTS_H
