// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMETAR_H
#define UTILITYMETAR_H

#include <QHash>
#include <QStringList>
#include "objects/FileStorage.h"
#include "objects/LatLon.h"
#include "radar/RID.h"

class UtilityMetar {
public:
    static RID findClosestObservation(const LatLon&);
    static void getStateMetarArrayForWXOGL(const QString&, FileStorage&);
    static QString getObservationSites(const QString&);
    static void readMetarData();
    static QStringList condenseObs(const QStringList&);
    static const QString metarFileName;
    static const QString pattern1;
    static const QString pattern2;
    static const QString pattern3;
    static const QString pattern4;
    static const QString pattern5;
    static bool initializedObsMap;
    static QHash<QString, LatLon> obsLatlon;
    static QStringList metarDataRaw;
    static QVector<RID> metarSites;
};

#endif  // UTILITYMETAR_H
