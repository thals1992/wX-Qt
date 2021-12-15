// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMATH_H
#define UTILITYMATH_H

#include <cmath>
#include <QString>
#include <QVector>

class UtilityMath {
public:
    static float distanceOfLine(float, float, float, float);
    static QVector<float> computeTipPoint(float, float, float, float, bool);
    static QVector<float> computeMiddlePoint(float, float, float, float, float);
    static float pixPerDegreeLon(float, float);
    static float degreesToRadians(float);
    static float deg2rad(float);
    static float rad2deg(float);
    static QString heatIndex(const QString&, const QString&);
    static QString convertWindDir(const QString&);
    static QString celsiusToFahrenheit(const QString&);
    static QString unitsPressure(const QString&);
};

#endif  // UTILITYMATH_H
