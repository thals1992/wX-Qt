// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLNEXRADLEVEL3STORMINFO_H
#define WXGLNEXRADLEVEL3STORMINFO_H

#include <QVector>
#include "external/ExternalGeodeticCalculator.h"
#include "external/ExternalGlobalCoordinates.h"
#include "objects/FileStorage.h"
#include "objects/LatLon.h"
#include "util/ProjectionNumbers.h"

class WXGLNexradLevel3StormInfo {
public:
    static void decode(const ProjectionNumbers&, FileStorage&);

private:
    static QVector<float> drawTickMarks(const LatLon&, const ProjectionNumbers&, const ExternalGlobalCoordinates&, float, float);
};

#endif  // WXGLNEXRADLEVEL3STORMINFO_H
