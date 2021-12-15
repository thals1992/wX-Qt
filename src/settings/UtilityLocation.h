// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYLOCATION_H
#define UTILITYLOCATION_H

#include "objects/LatLon.h"
#include "radar/RID.h"

class UtilityLocation {
public:
    static QVector<RID> getNearestRadarSites(const LatLon&, int, bool = true);
    static LatLon getSiteLocation(const QString&, const QString& = "RID");
    static QString getNearestOffice(const QString&, const LatLon&);
    static bool compareSites(const RID&, const RID&);
    static LatLon getCenterOfPolygon(const QVector<LatLon>&);
};

#endif  // UTILITYLOCATION_H
