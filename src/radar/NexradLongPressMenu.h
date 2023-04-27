// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NEXRADLONGPRESSMENU_H
#define NEXRADLONGPRESSMENU_H

#include <functional>
#include <vector>
#include <QWidget>
#include "objects/LatLon.h"
#include "radar/NexradState.h"
#include "radar/PolygonType.h"
#include "ui/ComboBox.h"

using std::function;
using std::vector;

class NexradLongPressMenu {
public:
    static void setupContextMenu(
        QWidget *,
        const QPoint&,
        const NexradState&,
        const LatLon&,
        const function<void(int, string)>&,
        const function<void(int, string)>&
    );
};

#endif  // NEXRADLONGPRESSMENU_H
