// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityNexradColors.h"
#include <QVector>
#include "objects/Color.h"

double UtilityNexradColors::interpolate(int a, int b, double proportion) {
    return a + ((b - a) * proportion);
}

double UtilityNexradColors::interpolateHue(int a, int b, double proportion) {
    auto diff = b - a;
    auto fudgeFactor = 0.01f;
    auto total = 360.0f;
    // hue ranges from 0-360
    if (diff > ((total / 2) - fudgeFactor)) {
        auto transformedColor = (total - (b - a)) * -1.0;
        if (transformedColor < 0) {
            transformedColor += total;
            return transformedColor;
        } else {
            return transformedColor;
        }
    } else {
        if (b > a) {
            return abs(a + (b - a) * proportion);
        } else {
            auto transformedColor = a + (b - a) * proportion;
            if (a > 270.0 && b < 90.0) {
                transformedColor = (a + (360.0 - a + b) * proportion);
            }
            return transformedColor;
        }
    }
}

int UtilityNexradColors::interpolateColor(int colorA, int colorB, double proportion) {
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
