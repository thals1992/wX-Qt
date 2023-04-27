// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTDATETIME_H
#define OBJECTDATETIME_H

#include <cstdint>
#include <string>
#include <QDateTime>
#include "radar/RID.h"

using std::string;

class ObjectDateTime {
public:
    ObjectDateTime();
    explicit ObjectDateTime(const QDateTime&);
    void addHours(int);
    void addSecs(int);
    bool isBefore(const ObjectDateTime&) const;
    string toString(const string&);
    string format(const string&);
    void utcToLocal();
    QDateTime get() const;
    static ObjectDateTime fromObs(const string&);
    static ObjectDateTime decodeVtecTime(const string&);
    static ObjectDateTime fromString(const string&, const string&);
    static ObjectDateTime parse(const string&, const string&);
    static QDateTime getCurrentTimeInUTC();
    static int offsetFromUtcInSeconds();
    static string getCurrentLocalTimeAsString();
    static string getLocalTimeAsString();
    static string getGmtTimeForVtec();
    static int64_t currentTimeMillis();
    static string dayOfWeekAbbreviation(int, int, int, int);
    static int getYear();
    static int getMonth();
    static int getDay();
    static int getHour();
    static int getMinute();
    static int getDayOfWeek();
    static int getCurrentHourInUTC();
    static bool timeDifference(const QDateTime&, const QDateTime&, int);
    static bool isDaytime(const RID&);
    static string getTimeFromPointAsString(uint64_t);
    static vector<string> generateModelRuns(const string&, int);
    static string translateTimeForHourly(const string&);
    static string getDayOfWeekForHourly(const string&);

private:
    static string getDateAsString(const string&);
    QDateTime dateTime;

};
QDebug operator<< (QDebug d, const ObjectDateTime&);

#endif  // OBJECTDATETIME_H
