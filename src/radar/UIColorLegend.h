// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UICOLORLEGEND_H
#define UICOLORLEGEND_H

#include <QFont>
#include <QPaintEvent>
#include <QPainter>
#include <QString>

class UIColorLegend {
public:
    UIColorLegend(const QString&);
    void paintEvent(QPainter &, float, float);

private:
    void drawRect(QPainter *, float, float, float, float);
    void drawText(QPainter *, const QString&, float, float);
    int setColor(int, int, int);
    void setColorWithBuffers(int, int);
    QString product;
    int screenHeight;
    int color;
    float scale;
    QFont qfont;
};

#endif  // UICOLORLEGEND_H
