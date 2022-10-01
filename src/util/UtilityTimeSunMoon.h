// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYTIMESUNMOON_H
#define UTILITYTIMESUNMOON_H

#include <string>
#include <vector>
#include <QTime>
#include "objects/LatLon.h"
#include "radar/RID.h"

using std::string;
using std::vector;

class UtilityTimeSunMoon {
public:
    static string getSunTimes(const LatLon&);
    static vector<QTime> getSunriseSunsetFromObs(const RID&);
};

#endif  // UTILITYTIMESUNMOON_H
