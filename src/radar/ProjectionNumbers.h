// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef PROJECTIONNUMBERS_H
#define PROJECTIONNUMBERS_H

#include <string>

using std::string;

class ProjectionNumbers {
public:
    ProjectionNumbers();
    void setRadarSite(const string&);
    double xCenter{};
    double yCenter{};
    double oneDegreeScaleFactor{};
    double x() const;
    double y() const;
    double getOneDegreeScaleFactor() const;
    string getRadarSite() const;

private:
    string radarSite;
    string latString;
    string lonString;
    double scale{};
};

#endif  // PROJECTIONNUMBERS_H
