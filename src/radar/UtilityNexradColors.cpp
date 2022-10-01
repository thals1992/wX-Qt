// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityNexradColors.h"
#include "objects/Color.h"

double UtilityNexradColors::interpolate(double a, double b, double proportion) {
    return a + ((b - a) * proportion);
}

double UtilityNexradColors::interpolateHue(double colorA, double colorB, double proportion) {
    const auto diff = colorB - colorA;
    auto total = 1.0;
    if (diff > total / 2) {
        const auto ret = (total - (colorB - colorA)) * -1.0;
        if (ret < 0) {
            return ret + total;
        }
        return ret;
    }
    return colorA + ((colorB - colorA) * proportion);
}

// double UtilityNexradColors::interpolateHue(double a, double b, double proportion) {
//    auto diff = b - a;
// //    auto fudgeFactor = 0.01;
//    auto total = 360.0;
//    // hue ranges from 0-360
//    if (diff > (total / 2)) {
//        auto transformedColor = (total - (b - a)) * -1.0;
//        if (transformedColor < 0.0) {
//            transformedColor += total;
//            return transformedColor;
//        } else {
//            return transformedColor;
//        }
//    } else {
// //        return a + ((b - a) * proportion);
//        if (b > a) {
//            return abs(a + (b - a) * proportion);
//        } else {
//            auto transformedColor = a + (b - a) * proportion;
//            if (a > 270.0 && b < 90.0) {
//                transformedColor = (a + (360.0 - a + b) * proportion);
//            }
//            return transformedColor;
//        }
//    }
// }

vector<double> UtilityNexradColors::interpolateColor(const vector<double>& colorA, const vector<double>& colorB, double proportion) {
    auto hsva = Color::colorToHsv(colorA);
    auto hsvb = Color::colorToHsv(colorB);
    for (auto index : {0, 1, 2}) {
        if (index > 0) {
            hsvb[index] = interpolate(hsva[index], hsvb[index], proportion);
        } else {
            hsvb[index] = interpolateHue(hsva[index], hsvb[index], proportion);
        }
    }
    return Color::hsvToColor(hsvb);
}
