// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef PROJECTIONNUMBERS_H
#define PROJECTIONNUMBERS_H

#include <QString>

class ProjectionNumbers {
public:
    ProjectionNumbers();
    explicit ProjectionNumbers(const QString&);
    QString radarSite;
    float xCenter;
    float yCenter;
    float oneDegreeScaleFactor;
    float xDbl() const;
    float yDbl() const;
    float getOneDegreeScaleFactor() const;

private:
    QString lat;
    QString lon;
    float scale;
};

#endif  // PROJECTIONNUMBERS_H
