// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NEXRADDRAW_H
#define NEXRADDRAW_H

#include <vector>
#include <QLineF>
#include <QPolygonF>
#include <QVector>
#include "objects/FileStorage.h"
#include "objects/MemoryBuffer.h"
#include "radar/NexradState.h"
#include "radar/RadarGeometryTypeEnum.h"
#include "radar/NexradRenderTextObject.h"
#include "ui/TextViewMetal.h"

using std::vector;

class NexradDraw {
public:
    NexradDraw(NexradState *, FileStorage *, NexradRenderTextObject *);
    void initGeom();
    void convertGeomData(RadarGeometryTypeEnum type);
    void drawGenericCircles(QPainter&, double, const QColor&, const vector<double>&);
    void drawWbCircles(QPainter&, double, const vector<QColor>&, const vector<vector<double>>&);
//    static void drawLocationCircle(QPainter&, const NexradState&, double, const QColor&, const QVector<float>&);
    void drawGenericLine(QPainter&, double, const QColor&, const QVector<QLineF>&);
    void drawGeomLine(QPainter&, RadarGeometryTypeEnum);
    void drawTriangles(QPainter&, const QColor&, vector<QPolygonF>&);
    void drawText(QPainter&, const QColor&, const vector<TextViewMetal>&);

private:
    static constexpr double xShift{-1.0};
    static constexpr double yShift{1.0};
    NexradState * nexradState;
    FileStorage * fileStorage;
    NexradRenderTextObject * textObject;
};

#endif  // NEXRADDRAW_H
