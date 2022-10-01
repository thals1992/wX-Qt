// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMATH_H
#define UTILITYMATH_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class UtilityMath {
public:
    static double distanceOfLine(double, double, double, double);
    static vector<double> computeTipPoint(double, double, double, double, bool);
    static vector<double> computeMiddlePoint(double, double, double, double, double);
    static double pixPerDegreeLon(double, double);
    static double degreesToRadians(double);
    static double deg2rad(double);
    static double rad2deg(double);
    static string heatIndex(const string&, const string&);
    static string convertWindDir(const string&);
    static string celsiusToFahrenheit(const string&);
    static string unitsPressure(const string&);
};

#endif  // UTILITYMATH_H
