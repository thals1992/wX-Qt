// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYRADARUI_H
#define UTILITYRADARUI_H

#include <QWidget>
#include "objects/LatLon.h"
#include "radar/NexradState.h"
#include "radar/PolygonType.h"

class UtilityRadarUI {
public:
    static void showPolygonText(QWidget *, const LatLon&);
    static void showNearestProduct(QWidget *, PolygonType, const LatLon&);
    static LatLon getLatLonFromScreenPosition(const NexradState&, float, float, float);
    static QString getRadarStatusMessage(const QString&);
};

#endif  // UTILITYRADARUI_H
