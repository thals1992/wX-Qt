// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPOTTERREPORTS_H
#define SPOTTERREPORTS_H

#include <QString>
#include "objects/LatLon.h"

class SpotterReports {
public:
    SpotterReports();
    SpotterReports(const QString&, const QString&, const LatLon&, const QString&, const QString&, const QString&, const QString&, const QString&);
    QString firstName;
    QString lastName;
    LatLon location;
    QString narrative;
    QString uniq;
    QString reportType;
    QString time;
    QString city;
};

#endif  // SPOTTERREPORTS_H
