// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityMath.h"
#include <cmath>
#include <numbers>
#include "util/To.h"

double UtilityMath::distanceOfLine(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

vector<double> UtilityMath::computeTipPoint(double x0, double y0, double x1, double y1, bool right) {
    const auto dx = x1 - x0;
    const auto dy = y1 - y0;
    const auto length = sqrt(dx * dx + dy * dy);
    const auto dirX = dx / length;
    const auto dirY = dy / length;
    const auto height = sqrt(3) / 2 * length;
    const auto cx = x0 + dx * 0.5;
    const auto cy = y0 + dy * 0.5;
    const auto pDirX = -dirY;
    const auto pDirY = dirX;
    if (right)
        return {cx + height * pDirX, cy + height * pDirY};
    else
        return {cx - height * pDirX, cy - height * pDirY};
}

vector<double> UtilityMath::computeMiddlePoint(double x0, double y0, double x1, double y1, double fraction) {
    return {x0 + fraction * (x1 - x0), y0 + fraction * (y1 - y0)};
}

double UtilityMath::pixPerDegreeLon(double centerX, double factor) {
    auto radius = (180.0 / std::numbers::pi) * (1.0 / cos(degreesToRadians(30.51))) * factor;
    return radius * (std::numbers::pi / 180.0) * cos(degreesToRadians(centerX));
}

double UtilityMath::degreesToRadians(double deg) {
    return deg * std::numbers::pi / 180.0;
}

double UtilityMath::deg2rad(double deg) {
    return deg * std::numbers::pi / 180.0;
}

double UtilityMath::rad2deg(double rad) {
    return rad * 180.0 / std::numbers::pi;
}

string UtilityMath::heatIndex(const string& temp, const string& RH) {
    // temp >= 80 and RH >= 40;
    const auto T = To::Double(temp);
    const auto R = To::Double(RH);
    if (T > 80.0 && R > 4.0) {
        const auto s1 = -42.379;
        const auto s2 = 2.04901523 * T;
        const auto s3 = 10.14333127 * R;
        const auto s4 = 0.22475541 * T * R;
        const auto s5 = 6.83783 * pow(10.0, -3.0) * pow(T, 2.0);
        const auto s6 = 5.481717 * pow(10.0, -2.0) * pow(R, 2.0);
        const auto s7 = 1.22874 * pow(10.0, -3.0) * pow(T, 2.0) * R;
        const auto s8 = 8.5282 * pow(10.0, -4.0) * T * pow(R, 2.0);
        const auto s9 = 1.99 * pow(10.0, -6.0) * pow(T, 2.0) * pow(R, 2.0);
        const auto heatIndexInt = round(s1 + s2 + s3 - s4 - s5 - s6 + s7 + s8 - s9);
        if (heatIndexInt <= T) {
            return "";
        }
        return To::string(heatIndexInt);
    } else {
        return "";
    }
}

string UtilityMath::convertWindDir(const string& direction) {
    const vector<string> windDirections{"N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW", "N"};
    const auto normalizedDirection = To::Int(direction) % 360;
    const auto listIndex = static_cast<int>(round((static_cast<int>(normalizedDirection) / 22.5)));
    return windDirections[listIndex];
}

string UtilityMath::celsiusToFahrenheit(const string& value) {
    return To::string(round(To::Double(value) * 9.0 / 5.0 + 32.0));
}

string UtilityMath::unitsPressure(const string& value) {
    const auto number = To::Double(value) * 33.8637526;
    return To::string(round(number)) + " mb";
}
