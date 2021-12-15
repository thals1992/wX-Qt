// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTMETALRADARBUFFERS_H
#define OBJECTMETALRADARBUFFERS_H

#include <cstdint>
#include <QColor>
#include <QPolygonF>
#include <QPen>
#include <QBrush>
#include "objects/FileStorage.h"

class ObjectMetalRadarBuffers {
public:
    ObjectMetalRadarBuffers();
    explicit ObjectMetalRadarBuffers(FileStorage *);
    void initialize();
    void setToPositionZero();
    int animationIndex;
    FileStorage * fileStorage;
    int numberOfRadials;
    int numberOfRangeBins;
    double binSize;
    int16_t productCode;
    QVector<QColor> color;
    MemoryBuffer floatBuffer;
    MemoryBuffer colorBuffer;
    QVector<QPolygonF> rectPoints;
    QVector<QPen> colorPens;
    QVector<QBrush> colorBrushes;
};

#endif  // OBJECTMETALRADARBUFFERS_H
