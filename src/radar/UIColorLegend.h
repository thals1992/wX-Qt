// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UICOLORLEGEND_H
#define UICOLORLEGEND_H

#include <string>
#include <QFont>
#include <QPaintEvent>
#include <QPainter>

using std::string;

class UIColorLegend {
public:
    explicit UIColorLegend(const string&);
    void paintEvent(QPainter &, double, double, double);
    void update(const string&);

private:
    void drawRect(QPainter *, double, double, double, double) const;
    void drawText(QPainter *, const string&, double, double);
    static int setColor(int, int, int);
    void setColorWithBuffers(int, int);
    string product;
    int screenHeight{};
    int color{};
    QFont qfont;
};

#endif  // UICOLORLEGEND_H
