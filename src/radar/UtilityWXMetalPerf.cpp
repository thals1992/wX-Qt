// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityWXMetalPerf.h"
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
#include "radarcolorpalette/ObjectColorPalette.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"

using std::vector;

int UtilityWXMetalPerf::decode8BitAndGenRadials(ObjectMetalRadarBuffers * radarBuffers, FileStorage * fileStorage) {
    const auto k180DivPi = 180.0 / std::numbers::pi;
    auto totalBins = 0;
    MemoryBuffer * disFirst;
    if (radarBuffers->animationIndex == -1) {
        disFirst = &(fileStorage->memoryBuffer);
        disFirst->setPosition(0);
    } else {
        disFirst = &(fileStorage->animationMemoryBuffer[radarBuffers->animationIndex]);
        disFirst->setPosition(0);
    }
    if (disFirst->getCapacity() == 0) {
        return 0;
    }
    while (disFirst->getShort() != -1) {}
    disFirst->skipBytes(100);
    const int64_t compressedFileSize = disFirst->getCapacity() - disFirst->getPosition();
    auto dis2 = UtilityIO::uncompress(disFirst->getConstData() + disFirst->getPosition(), compressedFileSize);
    dis2.skipBytes(30);
// TODO FIXME
//    radarBuffers->setBackgroundColor();
    auto angleNext = 0.0;
    auto angle0 = 0.0;
    auto numberOfRadials = radarBuffers->numberOfRadials;
    // specific for ports using Qt
    const auto xShift = 1.0;
    const auto yShift = -1.0;
    for (auto radial : range(numberOfRadials)) {
        const auto numberOfRleHalfWords = dis2.getUnsignedShort();
        const auto angle = (450.0 - (dis2.getUnsignedShort() / 10.0));
        dis2.skipBytes(2);
        if (radial < numberOfRadials - 1) {
            dis2.mark(dis2.getPosition());
            dis2.skipBytes(static_cast<int>(numberOfRleHalfWords) + 2);
            angleNext = 450.0 - (dis2.getUnsignedShort() / 10.0);
            dis2.reset();
        }
        auto level = 0;
        auto levelCount = 0;
        auto binStart = radarBuffers->binSize;
        if (radial == 0) {
            angle0 = angle;
        }
//        double angleV = angle0;
//        if (radial < numberOfRadials - 1) {
//            angleV = angleNext;
//        }
        auto angleV = angleNext;
        if (radial >= numberOfRadials - 1) {
            angleV = angle0;
        }
        const auto angleVCos = cos(angleV / k180DivPi);
        const auto angleVSin = sin(angleV / k180DivPi);

        const auto angleCos = cos(angle / k180DivPi);
        const auto angleSin = sin(angle / k180DivPi);
        for (auto bin = 0; bin < numberOfRleHalfWords; bin++) {
            int curLevel = dis2.get();
            if (bin == 0) {
                level = curLevel;
            }
            if (curLevel == level) {
                levelCount += 1;
            } else {
                // Since we will attempt to use the higher level QT painter we don't need a color per vertex,
                // and we can draw a polygon instead of two triangles
                // 1
                // const auto p1x = xShift * binStart * angleVCos;
                // const auto p1y = yShift * binStart * angleVSin;
                // 2
                // const auto p2x = xShift * (binStart + (radarBuffers->binSize * levelCount)) * angleVCos;
                // const auto p2y = yShift * (binStart + (radarBuffers->binSize * levelCount)) * angleVSin;

                // // 3
                // const auto p3x = xShift * (binStart + (radarBuffers->binSize * levelCount)) * angleCos;
                // const auto p3y = yShift * (binStart + (radarBuffers->binSize * levelCount)) * angleSin;
                // // 4
                // const auto p4x = xShift * binStart * angleCos;
                // const auto p4y = yShift * binStart * angleSin;

                radarBuffers->rectPoints.emplace_back(
                    QVector<QPointF>{
                        QPointF{xShift * binStart * angleVCos, yShift * binStart * angleVSin},
                        QPointF{xShift * (binStart + (radarBuffers->binSize * levelCount)) * angleVCos, yShift * (binStart + (radarBuffers->binSize * levelCount)) * angleVSin},
                        QPointF{xShift * (binStart + (radarBuffers->binSize * levelCount)) * angleCos, yShift * (binStart + (radarBuffers->binSize * levelCount)) * angleSin},
                        QPointF{xShift * binStart * angleCos, yShift * binStart * angleSin}});
                radarBuffers->color.emplace_back(
                    ObjectColorPalette::colorMap[radarBuffers->productCode]->redValues->get(level),
                    ObjectColorPalette::colorMap[radarBuffers->productCode]->greenValues->get(level),
                    ObjectColorPalette::colorMap[radarBuffers->productCode]->blueValues->get(level));
                radarBuffers->colorPens.emplace_back(radarBuffers->color.back(), 0.0, Qt::SolidLine);
                radarBuffers->colorBrushes.emplace_back(radarBuffers->color.back(), Qt::SolidPattern);

                totalBins += 1;
                level = curLevel;
                binStart = bin * radarBuffers->binSize;
                levelCount = 1;
            }
        }
    }
    // std::cout << radarBuffers->rectPoints.size() << std::endl;
    return totalBins;
}

int UtilityWXMetalPerf::genRadials(ObjectMetalRadarBuffers * radarBuffers) {
    const auto k180DivPi = 180.0 / std::numbers::pi;
    auto totalBins = 0;
    auto bI = 0;
    auto radarBlackHole = 4.0;
    auto radarBlackHoleAdd = 4.0;
    radarBuffers->setBackgroundColor();
    radarBuffers->radialStartAngle.setPosition(0);
    radarBuffers->binWord.setPosition(0);
    // specific for ports using Qt
    const auto xShift = 1.0;
    const auto yShift = -1.0;
    vector<uint16_t> fourBitCodes{56, 19, 181, 78, 80};
    if (contains(fourBitCodes, radarBuffers->productCode)) {
        radarBlackHole = 1.0;
        radarBlackHoleAdd = 0.0;
    }
    for (auto g : range(radarBuffers->numberOfRadials - 1)) {
        // since radial_start is constructed natively as opposed to read in
        // from bigendian file we have to use getFloatNative
        const auto angle = radarBuffers->radialStartAngle.getFloatNative(g * 4);
        int level = radarBuffers->binWord.get(bI);
        auto levelCount = 0;
        auto binStart = radarBlackHole;
        auto angleV = radarBuffers->radialStartAngle.getFloatNative(g * 4 + 4);
        if (g >= radarBuffers->numberOfRadials - 1) {
            angleV = radarBuffers->radialStartAngle.getFloatNative(0);
        }
        const auto angleVCos = cos(angleV / k180DivPi);
        const auto angleVSin = sin(angleV / k180DivPi);

        const auto angleCos = cos(angle / k180DivPi);
        const auto angleSin = sin(angle / k180DivPi);
        for (int bin = 0; bin < radarBuffers->numberOfRangeBins; bin++) {
            const int curLevel = radarBuffers->binWord.get(bI);
            bI += 1;
            if (curLevel == level) {
                levelCount += 1;
            } else {
                // // 1
                // const auto p1x = xShift * binStart * angleVCos;
                // const auto p1y = yShift * binStart * angleVSin;
                // // 2
                // const auto p2x = xShift * (binStart + radarBuffers->binSize * levelCount) * angleVCos;
                // const auto p2y = yShift * (binStart + radarBuffers->binSize * levelCount) * angleVSin;

                // // 3
                // const auto p3x = xShift * (binStart + radarBuffers->binSize * levelCount) * angleCos;
                // const auto p3y = yShift * (binStart + radarBuffers->binSize * levelCount) * angleSin;
                // // 4
                // const auto p4x = xShift * binStart * angleCos;
                // const auto p4y = yShift * binStart * angleSin;
                // radarBuffers->rectPoints.emplace_back(QVector<QPointF>{QPointF{p1x, p1y}, QPointF{p2x, p2y}, QPointF{p3x, p3y}, QPointF{p4x, p4y}});
                
                radarBuffers->rectPoints.emplace_back(
                    QVector<QPointF>{
                        QPointF{xShift * binStart * angleVCos, yShift * binStart * angleVSin},
                        QPointF{xShift * (binStart + (radarBuffers->binSize * levelCount)) * angleVCos, yShift * (binStart + (radarBuffers->binSize * levelCount)) * angleVSin},
                        QPointF{xShift * (binStart + (radarBuffers->binSize * levelCount)) * angleCos, yShift * (binStart + (radarBuffers->binSize * levelCount)) * angleSin},
                        QPointF{xShift * binStart * angleCos, yShift * binStart * angleSin}});

                radarBuffers->color.emplace_back(
                    ObjectColorPalette::colorMap[radarBuffers->productCode]->redValues->get(level),
                    ObjectColorPalette::colorMap[radarBuffers->productCode]->greenValues->get(level),
                    ObjectColorPalette::colorMap[radarBuffers->productCode]->blueValues->get(level));
                radarBuffers->colorPens.emplace_back(radarBuffers->color.back(), 0.0, Qt::SolidLine);
                radarBuffers->colorBrushes.emplace_back(radarBuffers->color.back(), Qt::SolidPattern);

                totalBins += 1;
                level = curLevel;
                binStart = bin * radarBuffers->binSize + radarBlackHoleAdd;
                levelCount = 1;
            }
        }
    }
    return totalBins;
}
