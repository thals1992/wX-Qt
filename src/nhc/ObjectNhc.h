// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTNHC_H
#define OBJECTNHC_H

#include <QStringList>
#include <QVector>
#include "nhc/ObjectNhcStormDetails.h"

class ObjectNhc {
public:
    ObjectNhc();
    void getTextData();
    void showTextData();
    QVector<ObjectNhcStormDetails> stormDataList;

private:
    QStringList ids;
    QStringList binNumbers;
    QStringList names;
    QStringList classifications;
    QStringList intensities;
    QStringList pressures;
    QStringList latitudes;
    QStringList longitudes;
    QStringList movementDirs;
    QStringList movementSpeeds;
    QStringList lastUpdates;
    QStringList statusList;
};

#endif  // OBJECTNHC_H
