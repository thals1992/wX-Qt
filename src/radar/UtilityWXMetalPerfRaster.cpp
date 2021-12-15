// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityWXMetalPerfRaster.h"
#include "radarcolorpalette/ObjectColorPalette.h"

int UtilityWXMetalPerfRaster::generate(WXMetalNexradLevelData * levelData) {
    auto totalBins = 0;
    auto curLevel = 0;
    auto numberOfRows = 0;
    auto binsPerRow = 0;
    auto scaleFactor = 0.0;
    auto xShift = 1.0;
    auto yShift = -1.0;
    levelData->radarBuffers->rectPoints.clear();
    levelData->radarBuffers->color.clear();
    switch (levelData->radarBuffers->productCode) {
        case 38:
            numberOfRows = 232;
            binsPerRow = 232;
            scaleFactor = 8.0;
            break;
        case 41:
        case 57:
            numberOfRows = 232;
            binsPerRow = 232;
            scaleFactor = 8.0;
            break;
        default:
            numberOfRows = 464;
            binsPerRow = 464;
            scaleFactor = 2.0;
            break;
    }
    int halfPoint = numberOfRows / 2;
    for (auto g = 0; g < numberOfRows; g++) {
        for (auto bin = 0; bin < binsPerRow; bin++) {
            curLevel = levelData->binWord.get(g * binsPerRow + bin);
            // 1
            float p1x = (xShift * ((bin - halfPoint) * scaleFactor));
            float p1y = (yShift * ((g - halfPoint) * scaleFactor * -1.0));
            // 2
            float p2x = (xShift * ((bin - halfPoint) * scaleFactor));
            float p2y = (yShift * ((g + 1 - halfPoint) * scaleFactor * -1.0));
            // 3
            float p3x = (xShift * ((bin + 1 - halfPoint) * scaleFactor));
            float p3y = (yShift * ((g + 1 - halfPoint) * scaleFactor * -1.0));
            // 4
            float p4x = (xShift * ((bin + 1 - halfPoint) * scaleFactor));
            float p4y = (yShift * ((g - halfPoint) * scaleFactor * -1.0));

            QPolygonF polygon;
            polygon.push_back(QPointF(p1x, p1y));
            polygon.push_back(QPointF(p2x, p2y));
            polygon.push_back(QPointF(p3x, p3y));
            polygon.push_back(QPointF(p4x, p4y));

            levelData->radarBuffers->rectPoints.push_back(polygon);
            levelData->radarBuffers->color.push_back(
                QColor(
                    ObjectColorPalette::colorMap[levelData->radarBuffers->productCode]->redValues->get(curLevel),
                    ObjectColorPalette::colorMap[levelData->radarBuffers->productCode]->greenValues->get(curLevel),
                    ObjectColorPalette::colorMap[levelData->radarBuffers->productCode]->blueValues->get(curLevel)
                )
            );
            levelData->radarBuffers->colorPens.push_back(QPen(levelData->radarBuffers->color.back(), 0.5, Qt::SolidLine));
            levelData->radarBuffers->colorBrushes.push_back(QBrush(levelData->radarBuffers->color.back(), Qt::SolidPattern));

            totalBins += 1;
        }
    }
    return totalBins;
}
