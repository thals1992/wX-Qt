// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RADARUTILITYAWCRADARMOSAIC_H
#define RADARUTILITYAWCRADARMOSAIC_H

#include <QHash>
#include <QString>
#include <QStringList>
#include "objects/LatLon.h"

class UtilityAwcRadarMosaic {
public:
    static const QString baseUrl;
    static const QStringList products;
    static const QStringList productLabels;
    static const QStringList sectors;
    static const QStringList sectorLabels;
    static QHash<QString, LatLon> sectorToLatLon;
    static QString getNearestMosaic(const LatLon&);
    static QString get(const QString&, const QString&);
    static QStringList getAnimation(const QString&, const QString&, int);
};

#endif  // RADARUTILITYAWCRADARMOSAIC_H
