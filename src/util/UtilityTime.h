// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYTIME_H
#define UTILITYTIME_H

#include <cstdint>
#include <QDateTime>
#include <QStringList>

class UtilityTime {
public:
    static QString monthWordToNumber(const QString&);
    static int secondsFromUTC();
    static int64_t currentTimeMillis();
    static int getCurrentHourInUTC();
    static bool isVtecCurrent(const QString&);
    static QDateTime decodeVtecTime(const QString&);
    static QString getGmtTimeForVtec();
    static int getYear();
    static int getMonth();
    static int getDay();
    static QString dayOfWeek(int, int, int);
    static QString hourlyDayOfWeek(QString);
    static QString getDateAsString(const QString&);
    static QString getDateUtcAsString(const QString&);
    static QString getCurrentLocalTimeAsString();
    static bool isRadarTimeOld(int);
    static QStringList genModelRuns(const QString&, int, const QString& = "yyyyMMddHH");
    static QString gmtTime();
    static QString localTime();
    static QString getLocalTimeAsString();
};

#endif  // UTILITYTIME_H
