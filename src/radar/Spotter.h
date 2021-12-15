// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPOTTER_H
#define SPOTTER_H

#include "objects/LatLon.h"

class Spotter {
public:
    Spotter();
    Spotter(const QString&, const QString&, const LatLon&, const QString&, const QString&, const QString&, const QString&);
    QString firstName;
    QString lastName;
    LatLon location;
    QString reportedAt;
    QString email;
    QString phone;
    QString uniq;
};

#endif  // SPOTTER_H
