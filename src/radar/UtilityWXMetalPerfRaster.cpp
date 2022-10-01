// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityWXMetalPerfRaster.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include "radarcolorpalette/ObjectColorPalette.h"
#include "util/UtilityList.h"

int UtilityWXMetalPerfRaster::generate(ObjectMetalRadarBuffers * radarBuffers, WXMetalNexradLevelData * levelData) {
    auto totalBins = 0;
    auto numberOfRows = 464;
    auto binsPerRow = 464;
    auto scaleFactor = 2.0;
    const auto xShift = 1.0;
    const auto yShift = -1.0;
    radarBuffers->setBackgroundColor();
    switch (levelData->radarBuffers.productCode) {
        case 38:
            numberOfRows = 232;
            binsPerRow = 232;
            scaleFactor = 8.0;
            break;
        case 41:
            numberOfRows = 232;
            binsPerRow = 232;
            scaleFactor = 8.0;
            break;
        case 57:
            numberOfRows = 232;
            binsPerRow = 232;
            scaleFactor = 8.0;
            break;
        default:
            break;
    }
    auto halfPoint = static_cast<int>(numberOfRows / 2);
    for (auto g : range(numberOfRows)) {
        for (auto bin = 0; bin < binsPerRow; bin++) {
            const auto curLevel = static_cast<int>(radarBuffers->binWord.get(g * binsPerRow + bin));

            // // 1
            // auto p1x = xShift * (bin - halfPoint) * scaleFactor;
            // auto p1y = yShift * (g - halfPoint) * scaleFactor * -1.0;
            // // 2
            // auto p2x = xShift * (bin - halfPoint) * scaleFactor;
            // auto p2y = yShift * (g + 1 - halfPoint) * scaleFactor * -1.0;
            // // 3
            // auto p3x = xShift * (bin + 1 - halfPoint) * scaleFactor;
            // auto p3y = yShift * (g + 1 - halfPoint) * scaleFactor * -1.0;
            // // 4
            // auto p4x = xShift * (bin + 1 - halfPoint) * scaleFactor;
            // auto p4y = yShift * (g - halfPoint) * scaleFactor * -1.0;
            // levelData->radarBuffers.rectPoints.emplace_back(QVector<QPointF>{QPointF{p1x, p1y}, QPointF{p2x, p2y}, QPointF{p3x, p3y}, QPointF{p4x, p4y}});

            levelData->radarBuffers.rectPoints.emplace_back(QVector<QPointF>{
                QPointF{xShift * (bin - halfPoint) * scaleFactor, yShift * (g - halfPoint) * scaleFactor * -1.0},
                QPointF{xShift * (bin - halfPoint) * scaleFactor, yShift * (g + 1 - halfPoint) * scaleFactor * -1.0},
                QPointF{xShift * (bin + 1 - halfPoint) * scaleFactor, yShift * (g + 1 - halfPoint) * scaleFactor * -1.0},
                QPointF{xShift * (bin + 1 - halfPoint) * scaleFactor, yShift * (g - halfPoint) * scaleFactor * -1.0}});


            levelData->radarBuffers.color.emplace_back(
                ObjectColorPalette::colorMap[levelData->radarBuffers.productCode]->redValues->get(curLevel),
                ObjectColorPalette::colorMap[levelData->radarBuffers.productCode]->greenValues->get(curLevel),
                ObjectColorPalette::colorMap[levelData->radarBuffers.productCode]->blueValues->get(curLevel));
            levelData->radarBuffers.colorPens.emplace_back(levelData->radarBuffers.color.back(), 0.5, Qt::SolidLine);
            levelData->radarBuffers.colorBrushes.emplace_back(levelData->radarBuffers.color.back(), Qt::SolidPattern);
            totalBins += 1;
        }
    }
    return totalBins;
}
