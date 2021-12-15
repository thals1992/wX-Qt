// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLPOLYGONWARNINGS_H
#define WXGLPOLYGONWARNINGS_H

#include <QVector>
#include "objects/ObjectPolygonWarning.h"
#include "radar/PolygonType.h"
#include "util/ProjectionNumbers.h"

class WXGLPolygonWarnings {
public:
    static QVector<float> addGeneric(const ProjectionNumbers& projectionNumbers, const ObjectPolygonWarning *);
    static QVector<float> add(const ProjectionNumbers&, const PolygonType&);
    static int getCount(const PolygonType&);
};

#endif  // WXGLPOLYGONWARNINGS_H
