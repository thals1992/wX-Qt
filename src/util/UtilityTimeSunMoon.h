// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYTIMESUNMOON_H
#define UTILITYTIMESUNMOON_H

#include <QTime>
#include <QVector>
#include "objects/LatLon.h"
#include "radar/RID.h"

class UtilityTimeSunMoon {
public:
    static QString getSunTimesForHomescreen();
    static QString getSunTimes(LatLon);
    static QVector<QTime> getSunriseSunsetFromObs(const RID&);
};

#endif  // UTILITYTIMESUNMOON_H
