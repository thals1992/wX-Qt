// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYRADARUI_H
#define UTILITYRADARUI_H

#include <functional>
#include <vector>
#include <QWidget>
#include "objects/LatLon.h"
#include "radar/NexradState.h"
#include "radar/PolygonType.h"
#include "ui/ComboBox.h"

using std::function;
using std::vector;

class NexradRenderUI {
public:
    static void showPolygonText(QWidget *, const LatLon&);
    static void showNearestProduct(QWidget *, PolygonType, const LatLon&);
    static LatLon getLatLonFromScreenPosition(const NexradState&, double, double);
    static void showRadarStatusMessage(QWidget *, const string&);
};

#endif  // UTILITYRADARUI_H
