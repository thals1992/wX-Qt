// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityMath.h"
#include <QStringList>
#include <iostream>
#include "util/To.h"

float UtilityMath::distanceOfLine(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

QVector<float> UtilityMath::computeTipPoint(float x0, float y0, float x1, float y1, bool right) {
    const float dx = x1 - x0;
    const float dy = y1 - y0;
    const float length = sqrt(dx * dx + dy * dy);
    const float dirX = dx / length;
    const float dirY = dy / length;
    const float height = sqrt(3) / 2 * length;
    const float cx = x0 + dx * 0.5;
    const float cy = y0 + dy * 0.5;
    const float pDirX = -dirY;
    const float pDirY = dirX;
    if (right)
        return {cx + height * pDirX, cy + height * pDirY};
    else
        return {cx - height * pDirX, cy - height * pDirY};
}

QVector<float> UtilityMath::computeMiddlePoint(float x0, float y0, float x1, float y1, float fraction) {
    return {x0 + fraction * (x1 - x0), y0 + fraction * (y1 - y0)};
}

float UtilityMath::pixPerDegreeLon(float centerX, float factor) {
    const float radius = (180 / M_PI) * (1.0 / cos(degreesToRadians(30.51))) * factor;
    return radius * (M_PI / 180.0) * cos(degreesToRadians(centerX));
}

float UtilityMath::degreesToRadians(float deg) {
    return deg * M_PI / 180.0;
}

float UtilityMath::deg2rad(float deg) {
    return (deg * M_PI / 180.0);
}

float UtilityMath::rad2deg(float rad) {
    return (rad * 180.0 / M_PI);
}

QString UtilityMath::heatIndex(const QString& temp, const QString& RH) {
    // temp >= 80 and RH >= 40;
    const auto T = To::Float(temp);
    const auto R = To::Float(RH);
    if (T > 80.0 && R > 4.0) {
        const float s1 = -42.379;
        const float s2 = 2.04901523 * T;
        const float s3 = 10.14333127 * R;
        const float s4 = 0.22475541 * T * R;
        const float s5 = 6.83783 * pow(10.0, -3.0) * pow(T, 2.0);
        const float s6 = 5.481717 * pow(10.0, -2.0) * pow(R, 2.0);
        const float s7 = 1.22874 * pow(10.0, -3.0) * pow(T, 2.0) * R;
        const float s8 = 8.5282 * pow(10.0, -4.0) * T * pow(R, 2.0);
        const float s9 = 1.99 * pow(10.0, -6.0) * pow(T, 2.0) * pow(R, 2.0);
        const int heatIndexint = round(s1 + s2 + s3 - s4 - s5 - s6 + s7 + s8 - s9);
        if (heatIndexint <= T) {
            return "";
        }
        return To::String(heatIndexint);
    } else {
        return "";
    }
}

QString UtilityMath::convertWindDir(const QString& direction) {
    const QStringList windDirections = {"N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW", "N"};
    const auto normalizedDirection = To::Int(direction) % 360;
    const auto listIndex = static_cast<int>(round((static_cast<int>(normalizedDirection) / 22.5)));
    const auto windDirectionAsString = windDirections[listIndex];
    return windDirectionAsString;
}

QString UtilityMath::celsiusToFahrenheit(const QString& value) {
    return To::String(round((To::Float(value)) * 9 / 5 + 32));
}

QString UtilityMath::unitsPressure(const QString& value) {
    auto number = To::Float(value);
    number *= 33.8637526;
    return To::String(round(number)) + " mb";
}
