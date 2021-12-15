// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITY_H
#define UTILITY_H

#include <QVector>
#include "objects/LatLon.h"

class Utility {
public:
    static QString getRadarSiteName(const QString&);
    static LatLon getRadarSiteLatLon(const QString&);
    static QString getRadarSiteX(const QString&);
    static QString getRadarSiteY(const QString&);
    static LatLon getWfoSiteLatLon(const QString&);
    static LatLon getSoundingSiteLatLon(const QString&);
    static QString readPref(const QString&, const QString&);
    static int readPrefInt(const QString&, int);
    static void writePref(const QString&, const QString&);
    static void writePrefInt(const QString&, int);
    static QStringList prefGetAllKeys();
    static QString safeGet(const QStringList&, int);
};

#endif  // UTILITY_H
