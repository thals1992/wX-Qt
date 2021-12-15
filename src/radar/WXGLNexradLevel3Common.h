// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLNEXRADLEVEL3COMMON_H
#define WXGLNEXRADLEVEL3COMMON_H

#include <QVector>
#include "external/ExternalGeodeticCalculator.h"
#include "external/ExternalGlobalCoordinates.h"
#include "util/ProjectionNumbers.h"

class WXGLNexradLevel3Common {
public:
    static QVector<float> drawLine(const ExternalGlobalCoordinates&, const ProjectionNumbers&, float, float);
    static QVector<float> drawLine(QVector<float>, const ProjectionNumbers&, const ExternalGlobalCoordinates&, float, float);
    static QVector<float> computeMercatorNumbersFromEc(const ExternalGlobalCoordinates&, const ProjectionNumbers&);
};

#endif  // WXGLNEXRADLEVEL3COMMON_H
