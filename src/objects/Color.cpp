// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/Color.h"

const int Color::RED = -65536;
const int Color::GREEN = -16711936;
const int Color::YELLOW = -256;
const int Color::MAGENTA = -65281;

int Color::rgb(int red, int green, int blue) {
    int retVal = 255 << 24;
    retVal += (red << 16) + (green << 8) + blue;
    return retVal;
}

int Color::red(int color) {
    return static_cast<int>((color >> 16) & 255);
}

int Color::green(int color) {
    return static_cast<int>((color >> 8) & 255);
}

int Color::blue(int color) {
    return static_cast<int>(color & 255);
}

QColor Color::intToQColor(int colorAsInt) {
    auto redByte = red(colorAsInt);
    auto greenByte = green(colorAsInt);
    auto blueByte = blue(colorAsInt);
    return QColor(redByte, greenByte, blueByte);
}

int Color::qcolorToInt(QColor qcolor) {
    auto red = qcolor.red();
    auto green = qcolor.green();
    auto blue = qcolor.blue();
    return rgb(red, green, blue);
}

QVector<int> Color::colorToHsv(int color) {
    auto redInt = red(color);
    auto greenInt = green(color);
    auto blueInt = blue(color);
    QColor qcolor(redInt, greenInt, blueInt);
    return {qcolor.hue(), qcolor.saturation(), qcolor.value()};
}

int Color::hsvToColor(const QVector<int>& hsv) {
    QColor color;
    color.setHsv(hsv[0], hsv[1], hsv[2]);
    return Color::rgb(color.red(), color.green(), color.blue());
}

QColor Color::qtBlack() {
    return QColor::fromRgbF(0.0f, 0.0f, 0.0f);
}
