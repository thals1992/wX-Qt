// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTFORECAST_H
#define OBJECTFORECAST_H

#include <QString>

class ObjectForecast {
public:
    ObjectForecast();
    ObjectForecast(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&);
    QString name;
    QString temperature;
    QString windSpeed;
    QString windDirection;
    QString icon;
    QString shortForecast;
    QString detailedForecast;
};

#endif  // OBJECTFORECAST_H
