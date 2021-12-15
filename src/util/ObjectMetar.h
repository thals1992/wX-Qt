// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTMETAR_H
#define OBJECTMETAR_H

#include <QStringList>
#include "radar/RID.h"

class ObjectMetar {
public:
    explicit ObjectMetar(const LatLon&);
    QString changePressureUnits(const QString&) const;
    QString changeDegreeUnits(const QString&) const;
    QString decodeIconFromMetar(const QString&, const RID&) const;
    RID obsClosest;
    QString condition;
    QString temperature;
    QString dewPoint;
    QString windDirection;
    QString windSpeed;
    QString windGust;
    QString seaLevelPressure;
    QString visibility;
    QString relativeHumidity;
    QString windChill;
    QString heatIndex;
    QString conditionsTimeString;
    QString icon;
    QString rawMetar;
    QString metarData;
    QStringList metarDataList;
    static QString obsClosestClass;

private:
    QString metarSkyCondition;
    QString metarWeatherCondition;
    bool decodeIcon;
};

#endif  // OBJECTMETAR_H
