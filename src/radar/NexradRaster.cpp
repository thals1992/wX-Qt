// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradRaster.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include "radarcolorpalette/ColorPalette.h"
#include "util/UtilityList.h"

int NexradRaster::create(RadarBuffers * radarBuffers, NexradLevelData * levelData) {
    auto totalBins = 0;
    auto numberOfRows = 464;
    auto binsPerRow = 464;
    auto scaleFactor = 2.0;
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
            levelData->radarBuffers.rectPoints.emplace_back(QVector<QPointF>{
                QPointF{(bin - halfPoint) * scaleFactor, (g - halfPoint) * scaleFactor},
                QPointF{(bin - halfPoint) * scaleFactor, (g + 1 - halfPoint) * scaleFactor},
                QPointF{(bin + 1 - halfPoint) * scaleFactor, (g + 1 - halfPoint) * scaleFactor},
                QPointF{(bin + 1 - halfPoint) * scaleFactor, (g - halfPoint) * scaleFactor}});

            levelData->radarBuffers.color.emplace_back(
                ColorPalette::colorMap[levelData->radarBuffers.productCode]->redValues->get(curLevel),
                ColorPalette::colorMap[levelData->radarBuffers.productCode]->greenValues->get(curLevel),
                ColorPalette::colorMap[levelData->radarBuffers.productCode]->blueValues->get(curLevel));
            levelData->radarBuffers.colorPens.emplace_back(levelData->radarBuffers.color.back(), 0.5, Qt::SolidLine);
            levelData->radarBuffers.colorBrushes.emplace_back(levelData->radarBuffers.color.back(), Qt::SolidPattern);
            totalBins += 1;
        }
    }
    return totalBins;
}
