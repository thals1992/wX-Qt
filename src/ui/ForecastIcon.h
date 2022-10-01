// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef FORECASTICON_H
#define FORECASTICON_H

#include <string>
#include <QImage>
#include <QPainter>

using std::string;

class ForecastIcon {
public:
    explicit ForecastIcon(const string&);
    ForecastIcon(const string&, const string&);
    void drawLeftText(const string&);
    void drawRightText(const string&);
    void drawVerticalBar();
    void drawSingleText(const string&);
    QImage get();
    static QImage blankBitmap();

private:
    QImage image;
    QPainter painter;
    static const int dimensions;
    static const int numHeight;
    static const int halfWidth;
    static const QFont font;
    static const QPen penForText;
    static const QBrush brushForBar;
};

#endif  // FORECASTICON_H
