// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RADARGEOMETRY_H
#define RADARGEOMETRY_H

#include <QFile>
#include <QString>
#include <iostream>
#include "objects/MemoryBuffer.h"

class RadarGeometry {
public:
    static void initialize();
    static MemoryBuffer * stateRelativeBuffer;
    static MemoryBuffer * countyRelativeBuffer;
    static MemoryBuffer * hwRelativeBuffer;
    static MemoryBuffer * hwExtRelativeBuffer;
    static MemoryBuffer * lakeRelativeBuffer;
    static MemoryBuffer * caRelativeBuffer;
    static MemoryBuffer * mxRelativeBuffer;

private:
    static void loadData(const QString&, QByteArray&, MemoryBuffer**);
    static QByteArray stateRelativeByteArray;
    static QByteArray countyRelativeByteArray;
    static QByteArray hwRelativeByteArray;
    static QByteArray hwExtRelativeByteArray;
    static QByteArray lakeRelativeByteArray;
    static QByteArray caRelativeByteArray;
    static QByteArray mxRelativeByteArray;
};

#endif  // RADARGEOMETRY_H
