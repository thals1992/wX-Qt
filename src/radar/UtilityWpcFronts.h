// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYWPCFRONTS_H
#define UTILITYWPCFRONTS_H

#include <QStringList>
#include <QVector>
#include "objects/DownloadTimer.h"
#include "radar/Fronts.h"
#include "radar/PressureCenter.h"

class UtilityWpcFronts {
public:
    static const QString separator;
    static QVector<PressureCenter> pressureCenters;
    static QVector<Fronts> fronts;
    static DownloadTimer timer;
    static void get();

private:
    static void addColdFrontTriangles(Fronts *, const QStringList&);
    static void addWarmFrontSemicircles(Fronts *, const QStringList&);
    static void addFrontDataStationaryWarm(Fronts *, const QStringList&);
    static void addFrontDataTrof(Fronts *, const QStringList&);
    static void addFrontData(Fronts *, const QStringList&);
    static QVector<float> parseLatLon(const QString&);
};

#endif  // UTILITYWPCFRONTS_H
