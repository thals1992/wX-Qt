// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYRADAR_H
#define UTILITYRADAR_H

#include <QHash>
#include <QString>

class UtilityRadar {
public:
    static const QHash<QString, QString> soundingIdToName;
    // static const QHash<QString, QString> wfoIdToName;
    static const QHash<QString, QString> radarIdToName;
    static const QHash<QString, QString> wfoSiteToLat;
    static const QHash<QString, QString> wfoSiteToLon;
    static const QHash<QString, QString> radarSiteToLat;
    static const QHash<QString, QString> radarSiteToLon;
    static const QHash<QString, QString> soundingSiteToLat;
    static const QHash<QString, QString> soundingSiteToLon;
};

#endif  // UTILITYRADAR_H
