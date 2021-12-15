// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTSEVENDAY_H
#define OBJECTSEVENDAY_H

#include <QStringList>
#include "objects/LatLon.h"

class ObjectSevenDay {
public:
    ObjectSevenDay();
    explicit ObjectSevenDay(const LatLon&);
    QStringList icons;
    QStringList shortForecasts;
    QStringList detailedForecasts;
    void process();

private:
    LatLon latLon;
};

#endif  // OBJECTSEVENDAY_H
