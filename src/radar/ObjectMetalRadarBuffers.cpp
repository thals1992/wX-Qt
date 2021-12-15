// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/ObjectMetalRadarBuffers.h"
#include <memory>
#include "objects/MemoryBuffer.h"

ObjectMetalRadarBuffers::ObjectMetalRadarBuffers() {
    numberOfRadials = 0;
    numberOfRangeBins = 0;
    binSize = 0.0;
    productCode = 0;
}

ObjectMetalRadarBuffers::ObjectMetalRadarBuffers(FileStorage * fileStorage) {
    numberOfRadials = 0;
    numberOfRangeBins = 0;
    binSize = 0.0;
    productCode = 0;
    this->fileStorage = fileStorage;
}

void ObjectMetalRadarBuffers::initialize() {
    if (productCode == 37 || productCode == 38 || productCode == 41 || productCode == 57) {
        if (floatBuffer.getCapacity() < (48 * 464 * 464)) {
            floatBuffer = MemoryBuffer(48 * 464 * 464);
        }
        if (colorBuffer.getCapacity() < (12 * 464 * 464)) {
            colorBuffer = MemoryBuffer(12 * 464 * 464);
        }
    } else {
        if (floatBuffer.getCapacity() < (32 * numberOfRadials * numberOfRangeBins)) {
            floatBuffer = MemoryBuffer(32 * numberOfRadials * numberOfRangeBins);
        }
        if ((colorBuffer.getCapacity() < 12 * numberOfRadials * numberOfRangeBins)) {
            colorBuffer = MemoryBuffer(12 * numberOfRadials * numberOfRangeBins);
        }
    }
    setToPositionZero();
}

void ObjectMetalRadarBuffers::setToPositionZero() {
    floatBuffer.setPosition(0);
    colorBuffer.setPosition(0);
}
