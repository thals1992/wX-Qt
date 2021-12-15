// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef COLOR_H
#define COLOR_H

#include <QColor>
#include <QVector>

class Color {
public:
    static int rgb(int, int, int);
    static int red(int);
    static int green(int);
    static int blue(int);
    static QColor intToQColor(int);
    static int qcolorToInt(QColor);
    static QVector<int> colorToHsv(int);
    static int hsvToColor(const QVector<int>&);
    static QColor qtBlack();
    static const int RED;
    static const int GREEN;
    static const int YELLOW;
    static const int MAGENTA;
};

#endif  // COLOR_H
