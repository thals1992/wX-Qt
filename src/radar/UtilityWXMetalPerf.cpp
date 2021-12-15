// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityWXMetalPerf.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <cmath>
#include <cstdint>
#include <iostream>
#include "external/bzlib.h"
#include "objects/Color.h"
#include "objects/MemoryBuffer.h"
#include "radarcolorpalette/ObjectColorPalette.h"
#include "util/UtilityIO.h"

int UtilityWXMetalPerf::decode8BitAndGenRadials(ObjectMetalRadarBuffers * radarBuffers, [[maybe_unused]] WXMetalNexradLevelData * rd) {
    const auto k180DivPi = 180.0 / M_PI;
    auto totalBins = 0;
    MemoryBuffer * disFirst;
    if (radarBuffers->animationIndex == -1) {
        disFirst = &(radarBuffers->fileStorage->memoryBuffer);
        disFirst->setPosition(0);
    } else {
        disFirst = &(radarBuffers->fileStorage->animationMemoryBuffer[radarBuffers->animationIndex]);
        disFirst->setPosition(0);
    }
    if (disFirst->getCapacity() == 0) {
        return 0;
    }
    while (disFirst->getShort() != -1) {}
    disFirst->skipBytes(100);
    int64_t compressedFileSize = disFirst->getCapacity() - disFirst->getPosition();
    MemoryBuffer * dis2 = UtilityIO::uncompress(disFirst->qbyteArray.data() + disFirst->getPosition(), compressedFileSize);
    dis2->skipBytes(30);
    radarBuffers->setToPositionZero();
    double angleV;
    auto angleNext = 0.0;
    auto angle0 = 0.0;
    auto numberOfRadials = 360;
    // specific for ports using Qt
    auto xShift = 1.0;
    auto yShift = -1.0;
    for (auto radial = 0; radial < numberOfRadials; radial++) {
        uint16_t numberOfRleHalfWords = dis2->getUnsignedShort();
        double angle = (450.0 - (dis2->getUnsignedShort() / 10.0));
        dis2->skipBytes(2);
        if (radial < numberOfRadials - 1) {
            dis2->mark(dis2->getPosition());
            dis2->skipBytes(static_cast<int>(numberOfRleHalfWords) + 2);
            angleNext = (450.0 - (dis2->getUnsignedShort() / 10.0));
            dis2->reset();
        }
        int level = 0;
        int levelCount = 0;
        double binStart = radarBuffers->binSize;
        if (radial == 0) {
            angle0 = angle;
        }
        if (radial < numberOfRadials - 1) {
            angleV = angleNext;
        } else {
            angleV = angle0;
        }
        for (auto bin = 0; bin < numberOfRleHalfWords; bin++) {
            int curLevel = dis2->get();
            if (bin == 0) {
                level = curLevel;
            }
            if (curLevel == level) {
                levelCount += 1;
            } else {
                // Since we will attempt to use the higher level QT painter we don't need a color per vertex
                // and we can draw a polygon instead of two triangles
                // thus we will comment out redundant point and color data
                float angleVCos = cos((angleV) / k180DivPi);
                float angleVSin = sin((angleV) / k180DivPi);
                // 1
                float p1x = (xShift * (binStart * angleVCos));
                float p1y = (yShift * (binStart * angleVSin));
                // 2
                float p2x = (xShift * ((binStart + (radarBuffers->binSize * levelCount)) * angleVCos));
                float p2y = (yShift * ((binStart + (radarBuffers->binSize * levelCount)) * angleVSin));
                float angleCos = cos(angle / k180DivPi);
                float angleSin = sin(angle / k180DivPi);
                // 3
                float p3x = (xShift * ((binStart + (radarBuffers->binSize * levelCount)) * angleCos));
                float p3y = (yShift * ((binStart + (radarBuffers->binSize * levelCount)) * angleSin));
                // 4
                float p4x = (xShift * (binStart * angleCos));
                float p4y = (yShift * (binStart * angleSin));

                QPolygonF polygon;
                polygon.push_back(QPointF(p1x, p1y));
                polygon.push_back(QPointF(p2x, p2y));
                polygon.push_back(QPointF(p3x, p3y));
                polygon.push_back(QPointF(p4x, p4y));

                radarBuffers->rectPoints.push_back(polygon);
                radarBuffers->color.push_back(QColor(
                    ObjectColorPalette::colorMap[radarBuffers->productCode]->redValues->get(level),
                    ObjectColorPalette::colorMap[radarBuffers->productCode]->greenValues->get(level),
                    ObjectColorPalette::colorMap[radarBuffers->productCode]->blueValues->get(level)));

                radarBuffers->colorPens.push_back(QPen(radarBuffers->color.back(), 0.5, Qt::SolidLine));
                radarBuffers->colorBrushes.push_back(QBrush(radarBuffers->color.back(), Qt::SolidPattern));

                totalBins += 1;
                level = curLevel;
                binStart = bin * radarBuffers->binSize;
                levelCount = 1;
            }
        }
    }
    delete dis2;
    return totalBins;
}

int UtilityWXMetalPerf::genRadials(ObjectMetalRadarBuffers * radarBuffers, WXMetalNexradLevelData * rd) {
    const auto k180DivPi = 180.0 / M_PI;
    auto totalBins = 0;
    auto bI = 0;
    auto radarBlackHole = 0.0;
    auto radarBlackHoleAdd = 0.0;
    radarBuffers->setToPositionZero();
    double angleV;
    // specific for ports using Qt
    auto xShift = 1.0;
    auto yShift = -1.0;
    QVector<int> fourBitCodes = {56, 19, 181, 78, 80};
    if (fourBitCodes.contains(radarBuffers->productCode)) {
        radarBlackHole = 1.0;
        radarBlackHoleAdd = 0.0;
    } else {
        radarBlackHole = 4.0;
        radarBlackHoleAdd = 4.0;
    }
    for (auto g = 0; g < radarBuffers->numberOfRadials; g++) {
        // since radial_start is constructed natively as opposed to read in
        // from bigendian file we have to use getFloatNatve
        double angle = rd->radialStartAngle.getFloatNative(g * 4);
        int level = rd->binWord.get(bI);
        auto levelCount = 0;
        double binStart = radarBlackHole;
        if (g < radarBuffers->numberOfRadials - 1) {
            angleV = rd->radialStartAngle.getFloatNative(g * 4 + 4);
        } else {
            angleV = rd->radialStartAngle.getFloatNative(0);
        }
        for (int bin = 0; bin < radarBuffers->numberOfRangeBins; bin++) {
            int curLevel = rd->binWord.get(bI);
            bI += 1;
            if (curLevel == level) {
                levelCount += 1;
            } else {
                float angleVCos = cos((angleV) / k180DivPi);
                float angleVSin = sin((angleV) / k180DivPi);
                // 1
                float p1x = (xShift * (binStart * angleVCos));
                float p1y = (yShift * (binStart * angleVSin));
                // 2
                float p2x = (xShift * ((binStart + radarBuffers->binSize * levelCount) * angleVCos));
                float p2y = (yShift * ((binStart + radarBuffers->binSize * levelCount) * angleVSin));
                float angleCos = cos(angle / k180DivPi);
                float angleSin = sin(angle / k180DivPi);
                // 3
                float p3x = (xShift * ((binStart + radarBuffers->binSize * levelCount) * angleCos));
                float p3y = (yShift * ((binStart + radarBuffers->binSize * levelCount) * angleSin));
                // 4
                float p4x = (xShift * (binStart * angleCos));
                float p4y = (yShift * (binStart * angleSin));

                QPolygonF polygon;
                polygon.push_back(QPointF(p1x, p1y));
                polygon.push_back(QPointF(p2x, p2y));
                polygon.push_back(QPointF(p3x, p3y));
                polygon.push_back(QPointF(p4x, p4y));
                radarBuffers->rectPoints.push_back(polygon);

                radarBuffers->color.push_back(QColor(
                    ObjectColorPalette::colorMap[radarBuffers->productCode]->redValues->get(level),
                    ObjectColorPalette::colorMap[radarBuffers->productCode]->greenValues->get(level),
                    ObjectColorPalette::colorMap[radarBuffers->productCode]->blueValues->get(level)));

                radarBuffers->colorPens.push_back(QPen(radarBuffers->color.back(), 0.5, Qt::SolidLine));
                radarBuffers->colorBrushes.push_back(QBrush(radarBuffers->color.back(), Qt::SolidPattern));

                totalBins += 1;
                level = curLevel;
                binStart = bin * radarBuffers->binSize + radarBlackHoleAdd;
                levelCount = 1;
            }
        }
    }
    return totalBins;
}
