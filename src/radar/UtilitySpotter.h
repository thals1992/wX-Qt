// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYSPOTTER_H
#define UTILITYSPOTTER_H

#include <QString>
#include <QVector>
#include "objects/DownloadTimer.h"
#include "radar/Spotter.h"
#include "radar/SpotterReports.h"

class UtilitySpotter {
public:
    static QVector<Spotter> spotterList;
    static QVector<SpotterReports> reportsList;
    static DownloadTimer timer;
    static QVector<float> lat;
    static QVector<float> lon;
    static QVector<Spotter> get();
    static void processReports(const QString&);
};

#endif  // UTILITYSPOTTER_H
