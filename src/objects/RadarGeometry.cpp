// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/RadarGeometry.h"
#include "common/GlobalVariables.h"

MemoryBuffer * RadarGeometry::stateRelativeBuffer;
MemoryBuffer * RadarGeometry::countyRelativeBuffer;
MemoryBuffer * RadarGeometry::hwRelativeBuffer;
MemoryBuffer * RadarGeometry::hwExtRelativeBuffer;
MemoryBuffer * RadarGeometry::lakeRelativeBuffer;
MemoryBuffer * RadarGeometry::caRelativeBuffer;
MemoryBuffer * RadarGeometry::mxRelativeBuffer;

QByteArray RadarGeometry::stateRelativeByteArray;
QByteArray RadarGeometry::countyRelativeByteArray;
QByteArray RadarGeometry::hwRelativeByteArray;
QByteArray RadarGeometry::hwExtRelativeByteArray;
QByteArray RadarGeometry::lakeRelativeByteArray;
QByteArray RadarGeometry::caRelativeByteArray;
QByteArray RadarGeometry::mxRelativeByteArray;

void RadarGeometry::initialize() {
    loadData("statev2.bin", stateRelativeByteArray, &stateRelativeBuffer);
    loadData("county.bin", countyRelativeByteArray, &countyRelativeBuffer);
    loadData("hwv4.bin", hwRelativeByteArray, &hwRelativeBuffer);
    loadData("hwv4ext.bin", hwExtRelativeByteArray, &hwExtRelativeBuffer);
    loadData("lakesv3.bin", lakeRelativeByteArray, &lakeRelativeBuffer);
    loadData("ca.bin", caRelativeByteArray, &caRelativeBuffer);
    loadData("mx.bin", mxRelativeByteArray, &mxRelativeBuffer);
}

void RadarGeometry::loadData(const QString& fileName, QByteArray& ba, MemoryBuffer** mb) {
    QFile file(GlobalVariables::resDir + fileName);
    file.open(QIODevice::ReadOnly);
    ba = file.readAll();
    *mb = new MemoryBuffer(ba);
    (*mb)->setPosition(0);
    if (file.isOpen()) {
        file.close();
    }
}
