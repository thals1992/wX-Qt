// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTMETALRADARBUFFERS_H
#define OBJECTMETALRADARBUFFERS_H

#include <cstdint>
#include <vector>
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QPolygonF>
#include "objects/MemoryBuffer.h"

using std::vector;

class RadarBuffers {
public:
    RadarBuffers();
    void initialize();
    void setBackgroundColor();
    int animationIndex{-1};
    int numberOfRadials{};
    int numberOfRangeBins{};
    double binSize{};
    uint16_t productCode{};
    vector<QColor> color;
    vector<QPolygonF> rectPoints;
    vector<QPen> colorPens;
    vector<QBrush> colorBrushes;
    MemoryBuffer radialStartAngle;
    MemoryBuffer binWord;
};

#endif  // OBJECTMETALRADARBUFFERS_H
