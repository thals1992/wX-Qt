// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradDecodeFourBit.h"
#include <QDebug>
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numbers>
#include <vector>
#include "objects/Color.h"
#include "objects/MemoryBuffer.h"
#include "radarcolorpalette/ColorPalette.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"

using std::vector;

int NexradDecodeFourBit::radial(RadarBuffers * radarBuffers, FileStorage * fileStorage) {
    MemoryBuffer * dis;
    if (radarBuffers->animationIndex == -1) {
        dis = &(fileStorage->memoryBuffer);
        dis->setPosition(0);
    } else {
        dis = &(fileStorage->animationMemoryBuffer[radarBuffers->animationIndex]);
        dis->setPosition(0);
    }
    if (dis->getCapacity() > 0) {
        dis->skipBytes(170);
        auto numberOfRangeBins = dis->getUnsignedShort();
        dis->skipBytes(6);
        dis->getUnsignedShort();
//        uint16_t numberOfRleHalfWords[360];
        radarBuffers->radialStartAngle.setPosition(0);
        for ([[maybe_unused]] auto i : range(360)) {
            auto numberOfRleHalfWord = dis->getUnsignedShort();
            auto rad = static_cast<float>(450.0 - (dis->getUnsignedShort() / 10.0));
            radarBuffers->radialStartAngle.putFloat(rad);
            dis->skipBytes(2);
            for (auto unused1 = 0; unused1 < numberOfRleHalfWord * 2; unused1++) {
                auto bin = dis->get();
                auto numOfBins = static_cast<int>(bin >> 4);
                for (auto unused2 = 0; unused2 < numOfBins; unused2++) {
                    radarBuffers->binWord.put(static_cast<int>(bin % 16));
                }
            }
        }
        return numberOfRangeBins;
    } else {
        return 230;
    }
}

int NexradDecodeFourBit::raster(RadarBuffers * radarBuffers, FileStorage * fileStorage) {
    MemoryBuffer * dis;
    if (radarBuffers->animationIndex == -1) {
        dis = &(fileStorage->memoryBuffer);
        dis->setPosition(0);
    } else {
        dis = &(fileStorage->animationMemoryBuffer[radarBuffers->animationIndex]);
        dis->setPosition(0);
    }
    if (dis->getCapacity() > 0) {
        dis->skipBytes(172);
        // let iCoordinateStart = dis.getUnsignedShort()
        // let jCoordinateStart = dis.getUnsignedShort()
        // let xScaleInt = dis.getUnsignedShort()
        // let xScaleFractional = dis.getUnsignedShort()
        // let yScaleInt = dis.getUnsignedShort()
        // let yScaleFractional = dis.getUnsignedShort()
        // let numberOfRows = dis.getUnsignedShort()
        // let packingDescriptor = dis.getUnsignedShort()
        dis->getUnsignedShort();
        dis->getUnsignedShort();
        dis->getUnsignedShort();
        dis->getUnsignedShort();
        dis->getUnsignedShort();
        dis->getUnsignedShort();
        auto numberOfRows = dis->getUnsignedShort();
        dis->getUnsignedShort();
        // 464 rows in NCR
        // 232 rows in NCZ
        for (auto unused0 = 0; unused0 < numberOfRows; unused0++) {
            auto numberOfBytes = dis->getUnsignedShort();
            for (auto unused1 = 0; unused1 < numberOfBytes; unused1++) {
                auto bin = static_cast<int>(dis->get());
                auto numOfBins = static_cast<int>(bin >> 4);
                for (auto unused2 = 0; unused2 < numOfBins; unused2++) {
                    unsigned char color = bin % 16;
                    radarBuffers->binWord.put(color);
                }
            }
        }
    }
    return 0;
}