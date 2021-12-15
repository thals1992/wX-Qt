// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityTime.h"
#include "util/To.h"
#include "util/UtilityString.h"

QString UtilityTime::monthWordToNumber(const QString& monthF) {
    auto month = monthF;
    return month.replace("Jan", "01").replace("Feb", "02").replace("Mar", "03").replace("Apr", "04").replace("May", "05").replace("Jun", "06").replace("Jul", "07").replace("Aug", "08").replace("Sep", "09").replace("Oct", "10").replace("Nov", "11").replace("Dec", "12");
}

int UtilityTime::getYear() {
    return QDate::currentDate().year();
}

int UtilityTime::getMonth() {
    return QDate::currentDate().month();
}

int UtilityTime::getDay() {
    return QDate::currentDate().day();
}

// used by utilHourly*
QString UtilityTime::dayOfWeek(int year, int month, int day) {
    auto hour = 0;
    const auto localTime = QDateTime(QDate(year, month, day), QTime(hour, 0, 0));
    const auto dayIndex = localTime.date().dayOfWeek();
    QString dayOfTheWeek;
    switch (dayIndex) {
    case 1:
        dayOfTheWeek = "Mon";
        break;
    case 2:
        dayOfTheWeek = "Tue";
        break;
    case 3:
        dayOfTheWeek = "Wed";
        break;
    case 4:
        dayOfTheWeek = "Thu";
        break;
    case 5:
        dayOfTheWeek = "Fri";
        break;
    case 6:
        dayOfTheWeek = "Sat";
        break;
    case 7:
        dayOfTheWeek = "Sun";
        break;
    default:
        dayOfTheWeek = "";
        break;
    }
    return dayOfTheWeek;
}

QString UtilityTime::hourlyDayOfWeek(QString originalTime) {
    auto value = originalTime;
    value = value.replace("T", "-");
    auto originalTimeComponents = value.split("-");
    const auto year = To::Int(originalTimeComponents[0]);
    const auto month = To::Int(originalTimeComponents[1]);
    const auto day = To::Int(originalTimeComponents[2]);
    const auto hour = To::Int(originalTimeComponents[3].replace(":00:00", ""));
    const auto localTime = QDateTime(QDate(year, month, day), QTime(hour, 0, 0));
    const auto dayIndex = localTime.date().dayOfWeek();
    QString dayOfTheWeek;
    switch (dayIndex) {
    case 1:
        dayOfTheWeek = "Mon";
        break;
    case 2:
        dayOfTheWeek = "Tue";
        break;
    case 3:
        dayOfTheWeek = "Wed";
        break;
    case 4:
        dayOfTheWeek = "Thu";
        break;
    case 5:
        dayOfTheWeek = "Fri";
        break;
    case 6:
        dayOfTheWeek = "Sat";
        break;
    case 7:
        dayOfTheWeek = "Sun";
        break;
    default:
        dayOfTheWeek = "";
        break;
    }
    return dayOfTheWeek;
}

int UtilityTime::secondsFromUTC() {
    const auto dateTime1 = QDateTime::currentDateTime();
    const auto dateTime2 = QDateTime(dateTime1.date(), dateTime1.time(), Qt::UTC);
    return dateTime1.secsTo(dateTime2);
}

int64_t UtilityTime::currentTimeMillis() {
    QDateTime local(QDateTime::currentDateTime());
    return local.toMSecsSinceEpoch();
}

int UtilityTime::getCurrentHourInUTC() {
    QDateTime currentTime = QDateTime::currentDateTimeUtc();
    return currentTime.time().hour();
}

bool UtilityTime::isVtecCurrent(const QString& vtec) {
    // example "190512T1252Z-190512T1545Z"
    auto timeRange = UtilityString::parse(vtec, "-([0-9]{6}T[0-9]{4})Z");
    auto timeInMinutes = decodeVtecTime(timeRange);
    auto currentTimeInMinutes = decodeVtecTime(getGmtTimeForVtec());
    auto isItCurrent = currentTimeInMinutes < timeInMinutes;
    return isItCurrent;
}

QDateTime UtilityTime::decodeVtecTime(const QString& timeRange) {
    auto year = To::Int(("20" + UtilityString::parse(timeRange, "([0-9]{2})[0-9]{4}T[0-9]{4}")));
    auto month = To::Int(UtilityString::parse(timeRange, "[0-9]{2}([0-9]{2})[0-9]{2}T[0-9]{4}"));
    auto day = To::Int(UtilityString::parse(timeRange, "[0-9]{4}([0-9]{2})T[0-9]{4}"));
    auto hour = To::Int(UtilityString::parse(timeRange, "[0-9]{6}T([0-9]{2})[0-9]{2}"));
    auto minute = To::Int(UtilityString::parse(timeRange, "[0-9]{6}T[0-9]{2}([0-9]{2})"));
    return QDateTime(QDate(year, month, day), QTime(hour, minute, 0));
}

QString UtilityTime::getGmtTimeForVtec() {
    auto currentTime = QDateTime::currentDateTimeUtc();
    auto timeForVtec = currentTime.toString("yyMMddThhmm");
    return timeForVtec;
}

// not UTC
QString UtilityTime::getDateAsString(const QString& format) {
    auto currentTime = QDateTime::currentDateTime();
    auto timeAsString = currentTime.toString(format);
    return timeAsString;
}

// UTC
QString UtilityTime::getDateUtcAsString(const QString& format) {
    auto currentTime = QDateTime::currentDateTimeUtc();
    auto timeAsString = currentTime.toString(format);
    return timeAsString;
}

QString UtilityTime::getCurrentLocalTimeAsString() {
    auto time = getDateAsString("yyyy-MM-dd HH:mm:ss");
    return time;
}

bool UtilityTime::isRadarTimeOld(int radarMilli) {
    // 1 min is 60k ms
    if (radarMilli > 20 * 60000) {
        return true;
    }
    return false;
}

QStringList UtilityTime::genModelRuns(const QString& time1, int hours, const QString& dateStr) {
    auto dateObject = QDateTime::fromString(time1, dateStr);
    QStringList runs;
    for (auto index : {1, 2, 3, 4}) {
        float timeChange = 60.0 * 60.0 * static_cast<float>(hours) * static_cast<float>(index);
        QDateTime newDateTime = dateObject.addSecs(-1.0 * timeChange);
        runs.push_back(newDateTime.toString(dateStr));
    }
    return runs;
}

QString UtilityTime::gmtTime() {
    return getDateUtcAsString("MM-dd HH:mm") + " UTC";
}

QString UtilityTime::localTime() {
    return getDateAsString("MM-dd HH:mm");
}

QString UtilityTime::getLocalTimeAsString() {
    return getDateAsString("HH:mm:ss");
}
