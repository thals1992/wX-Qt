// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/Color.h"
#include <algorithm>
#include <cmath>
#include <cstdint>

const int Color::RED{-65536};
const int Color::GREEN{-16711936};
// const int Color::YELLOW{-256};
const int Color::MAGENTA{-65281};

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
    return {red(colorAsInt), green(colorAsInt), blue(colorAsInt)};
}

int Color::qcolorToInt(QColor qcolor) {
    return rgb(qcolor.red(), qcolor.green(), qcolor.blue());
}

// QVector<double> Color::colorToHsv(int color) {
//    auto redInt = red(color);
//    auto greenInt = green(color);
//    auto blueInt = blue(color);
//    auto qcolor = QColor(redInt, greenInt, blueInt);
//    return {qcolor.hueF(), qcolor.saturationF(), qcolor.valueF()};
// }

// int Color::hsvToColor(const QVector<double>& hsv) {
//    QColor color;
//    color.setHsvF(hsv[0], hsv[1], hsv[2]);
//    return Color::rgb(color.red(), color.green(), color.blue());
// }

QColor Color::qtBlack() {
    return QColor::fromRgbF(0.0f, 0.0f, 0.0f);
}

vector<double> Color::colorToHsv(const vector<double>& color) {
    // https://www.cs.rit.edu/~ncs/color/t_convert.html
    auto r = color[0];
    auto g = color[1];
    auto b = color[2];
    double h;
    double s;
    auto minV = std::min(r, g);
    minV = std::min(minV, b);
    auto maxV = std::max(r, g);
    maxV = std::max(maxV, b);

    // auto minV = r < g ? r : g;
    // minV = minV < b ? minV : b;
    // auto maxV = r > g ? r : g;
    // maxV = maxV > b ? maxV : b;

    auto v = maxV;                              // v
    auto delta = maxV - minV;
    if (delta < 0.00001) {
        return {0, 0, v};
    }
    if (maxV > 0.0) {  // NOTE: if Max is == 0, this divide would cause a crash
        s = (delta / maxV);
    } else {
        // if max is 0, then r = g = b = 0
        // s = 0, h is undefined
        return {NAN, 0.0, v};
    }
    if (r >= maxV) {                         // > is bogus, just keeps compiler happy
        h = (g - b) / delta;        // between yellow & magenta
    } else {
        if (g >= maxV) {
            h = 2.0 + (b - r) / delta;  // between cyan & yellow
        } else {
            h = 4.0 + (r - g) / delta;  // between magenta & cyan
        }
    }
    h *= 60.0;                              // degrees
    if (h < 0.0) {
        h += 360.0;
    }
    return {h / 360.0, s, v};
}

// input for all 3 double is in 0.0-1.0
vector<double> Color::hsvToColor(const vector<double>& hsv) {
    auto h = hsv[0];
    auto s = hsv[1];
    auto v = hsv[2];
    if (s <= 0.0) {
        return {v, v, v};
    }
    auto hh = h * 360.0;
    if (hh >= 360.0) {
        hh = 0.0;
    }
    hh /= 60.0;
    auto i = static_cast<int64_t>(hh);
    auto ff = hh - static_cast<double>(i);
    auto p = v * (1.0 - s);
    auto q = v * (1.0 - (s * ff));
    auto t = v * (1.0 - (s * (1.0 - ff)));
    switch (i) {
        case 0:
            return {v, t, p};
        case 1:
            return {q, v, p};
        case 2:
            return {p, v, t};
        case 3:
            return {p, q, v};
        case 4:
            return {t, p, v};
        case 5:
        default:
            return {v, p, q};
    }
}
