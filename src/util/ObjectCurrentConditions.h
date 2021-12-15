// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCURRENTCONDITIONS_H
#define OBJECTCURRENTCONDITIONS_H

#include <QStringList>
#include "objects/LatLon.h"

class ObjectCurrentConditions {
public:
    ObjectCurrentConditions();
    explicit ObjectCurrentConditions(const LatLon&);
    void process();
    void formatCurrentConditions();
    QString getObsFullName();
    QString summary;
    QString temperature;
    QString windChill;
    QString heatIndex;
    QString dewPoint;
    QString relativeHumidity;
    QString seaLevelPressure;
    QString windDirection;
    QString windSpeed;
    QString windGust;
    QString visibility;
    QString condition;
    QString conditionsTimeString;
    QString obsStation;
    QStringList conditions;
    QString data;
    QString iconUrl;
    QString rawMetar;
    QString status;
    QString topLine;
    QString middleLine;
    QString bottomLine;

private:
    LatLon latLon;
};

#endif  // OBJECTCURRENTCONDITIONS_H
