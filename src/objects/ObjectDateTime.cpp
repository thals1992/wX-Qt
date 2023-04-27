// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/ObjectDateTime.h"
#include <QDebug>
#include <QString>
#include <QTimeZone>
#include <vector>
#include "objects/WString.h"
#include "util/To.h"
#include "util/UtilityString.h"
#include "util/UtilityTimeSunMoon.h"

ObjectDateTime::ObjectDateTime()
    : dateTime{ QDateTime::currentDateTimeUtc() }
{}

ObjectDateTime::ObjectDateTime(const QDateTime& dateTime)
    : dateTime{ QDateTime{dateTime} }
{}

// KEEP
// void ObjectDateTime::addDays(int i) {
//    dateTime = dateTime.addDays(i);
// }

void ObjectDateTime::addHours(int i) {
    dateTime = dateTime.addSecs(i * 60 * 60);
}

void ObjectDateTime::addSecs(int i) {
    dateTime = dateTime.addSecs(i);
}

// KEEP
// bool ObjectDateTime::isAfter(const ObjectDateTime& dt) const {
//    return dateTime > dt.get();
// }

bool ObjectDateTime::isBefore(const ObjectDateTime& dt) const {
    return dateTime < dt.get();
}

string ObjectDateTime::toString(const string& s) {
    return dateTime.toString(QString::fromStdString(s)).toStdString();
}

string ObjectDateTime::format(const string& s) {
    return dateTime.toString(QString::fromStdString(s)).toStdString();
}

void ObjectDateTime::utcToLocal() {
    dateTime.setTimeSpec(Qt::UTC);
    dateTime = dateTime.toLocalTime();
}

QDateTime ObjectDateTime::get() const {
    return dateTime;
}

ObjectDateTime ObjectDateTime::fromObs(const string& time) {
    // time comes in as follows 2018.02.11 2353 UTC
    // https://en.wikipedia.org/wiki/ISO_8601
    auto returnTime = WString::strip(time);
    returnTime = WString::replace(returnTime, " UTC", "");
    returnTime = WString::replace(returnTime, ".", "");
    returnTime = WString::replace(returnTime, " ", "T") + "00.000Z";
    // time should now be as "20220225T095300.000Z"
    // text has a timezone "Z" so 2nd arg is null
    // qDebug() << "decode:" << returnTime;
    auto dateTime = QDateTime::fromString(QString::fromStdString(returnTime), "yyyyMMddThhmmss.zzzZ");
    dateTime.setTimeSpec(Qt::UTC);
    if (!dateTime.isValid()) {
        dateTime = getCurrentTimeInUTC();
    }
    auto objectDateTime = ObjectDateTime{};
    objectDateTime.dateTime = dateTime;
    return objectDateTime;
}

ObjectDateTime ObjectDateTime::decodeVtecTime(const string& timeRange) {
    const auto year = To::Int(("20" + UtilityString::parse(timeRange, "([0-9]{2})[0-9]{4}T[0-9]{4}")));
    const auto month = To::Int(UtilityString::parse(timeRange, "[0-9]{2}([0-9]{2})[0-9]{2}T[0-9]{4}"));
    const auto day = To::Int(UtilityString::parse(timeRange, "[0-9]{4}([0-9]{2})T[0-9]{4}"));
    const auto hour = To::Int(UtilityString::parse(timeRange, "[0-9]{6}T([0-9]{2})[0-9]{2}"));
    const auto minute = To::Int(UtilityString::parse(timeRange, "[0-9]{6}T[0-9]{2}([0-9]{2})"));
    auto objectDateTime = ObjectDateTime{QDateTime(QDate{year, month, day}, QTime{hour, minute, 0}, QTimeZone::utc())};
    if (!objectDateTime.get().isValid()) {
        // qDebug() << "NULL" << timeRange;
        objectDateTime = ObjectDateTime{getCurrentTimeInUTC()};
        objectDateTime.addHours(1);
    }
    return objectDateTime;
}

ObjectDateTime ObjectDateTime::fromString(const string& time, const string& format) {
    auto dateTime = QDateTime::fromString(QString::fromStdString(time), QString::fromStdString(format));
    return ObjectDateTime{dateTime};
}

ObjectDateTime ObjectDateTime::parse(const string& time, const string& format) {
    auto dateTime = QDateTime::fromString(QString::fromStdString(time), QString::fromStdString(format));
    return ObjectDateTime{dateTime};
}

QDateTime ObjectDateTime::getCurrentTimeInUTC() {
    return QDateTime::currentDateTimeUtc();
}

int ObjectDateTime::offsetFromUtcInSeconds() {
    const auto dateTime1 = QDateTime::currentDateTime();
    const auto dateTime2 = QDateTime{dateTime1.date(), dateTime1.time(), Qt::UTC};
    return static_cast<int>(dateTime1.secsTo(dateTime2));
}

// not UTC
string ObjectDateTime::getDateAsString(const string& format) {
    const auto currentTime = QDateTime::currentDateTime();
    return currentTime.toString(QString::fromStdString(format)).toStdString();
}

// TODO FIXME remove in favor of below
string ObjectDateTime::getCurrentLocalTimeAsString() {
    return getDateAsString("yyyy-MM-dd HH:mm:ss");
}

string ObjectDateTime::getLocalTimeAsString() {
    return getDateAsString("HH:mm:ss");
}

string ObjectDateTime::getGmtTimeForVtec() {
    const auto currentTime = QDateTime::currentDateTimeUtc();
    return currentTime.toString("yyMMddThhmm").toStdString();
}

int64_t ObjectDateTime::currentTimeMillis() {
    auto local = QDateTime::currentDateTime();
    return local.toMSecsSinceEpoch();
}

// used by UtilityHourlyOldApi.cpp
string ObjectDateTime::dayOfWeekAbbreviation(int year, int month, int day, int hour) {
    const auto localTime = QDateTime{QDate{year, month, day}, QTime{hour, 0, 0}};
    return localTime.toString("ddd").toStdString();
}

int ObjectDateTime::getYear() {
    return QDate::currentDate().year();
}

int ObjectDateTime::getMonth() {
    return QDate::currentDate().month();
}

int ObjectDateTime::getDay() {
    return QDate::currentDate().day();
}

int ObjectDateTime::getHour() {
    const time_t theTime = time(nullptr);
    const struct tm *aTime = localtime(&theTime);
    const int hour = aTime->tm_hour;
    return hour;
}

int ObjectDateTime::getMinute() {
    const time_t theTime = time(nullptr);
    const struct tm *aTime = localtime(&theTime);
    const int min = aTime->tm_min;
    return min;
}

int ObjectDateTime::getDayOfWeek() {
    // wxDateTime now = wxDateTime::Now(); // .MakeUTC().Format().c_str()
    // return now.GetDay();
    return QDate::currentDate().dayOfWeek();
}

int ObjectDateTime::getCurrentHourInUTC() {
    const auto currentTime = QDateTime::currentDateTimeUtc();
    return currentTime.time().hour();
}

bool ObjectDateTime::timeDifference(const QDateTime& t1, const QDateTime& t2, int m) {
    auto date = t2.addSecs(m * 60);
    return date > t1;
}

bool ObjectDateTime::isDaytime(const RID& obs) {
    // 2 element list with sunrise 1st, sunrise 2nd
    const auto sunTimes = UtilityTimeSunMoon::getSunriseSunsetFromObs(obs);
    const auto currentTime = QTime::currentTime();
    return !(currentTime > sunTimes[1] || currentTime < sunTimes[0]);
}

string ObjectDateTime::getTimeFromPointAsString(uint64_t sec) {
    const auto radarTime = QDateTime::fromMSecsSinceEpoch(sec * 1000);
    return radarTime.toString("hh:mm:ss").toStdString();
}

vector<string> ObjectDateTime::generateModelRuns([[maybe_unused]] const string& time1, [[maybe_unused]] int hours) {  // wxc2 has 3rd arg , QString dateStr
    // TODO FIXME
    //  QDateTime dateObject = QDateTime::fromString(time1, dateStr);
    vector<string> runs;
    //  for (int index = 1; index < 5; index++) {
    //      float timeChange = 60.0 * 60.0 * float(hours) * float(index);
    //      QDateTime newDateTime = dateObject.addSecs(-1.0 * timeChange);
    //      runs.append(newDateTime.toString(dateStr));
    //  }
    return runs;
}

string ObjectDateTime::translateTimeForHourly(const string& originalTime) {
    auto value = originalTime;
    value = WString::replace(value, "T", "-");
    const auto originalTimeComponents = WString::split(value, "-");
    const auto hour = To::Int(WString::replace(originalTimeComponents[3], ":00:00", ""));
    return getDayOfWeekForHourly(originalTime) + " " + To::string(hour);
}

string ObjectDateTime::getDayOfWeekForHourly(const string& originalTime) {
    auto value = originalTime;
    value = WString::replace(value, "T", "-");
    auto originalTimeComponents = WString::split(value, "-");
    const auto year = To::Int(originalTimeComponents[0]);
    const auto month = To::Int(originalTimeComponents[1]);
    const auto day = To::Int(originalTimeComponents[2]);
    const auto hour = To::Int(WString::replace(originalTimeComponents[3], ":00:00", ""));
    return ObjectDateTime::dayOfWeekAbbreviation(year, month, day, hour);
}

QDebug operator<<(QDebug dbg, const ObjectDateTime &objectDateTime) {
    dbg.nospace() << objectDateTime.get().toString() << " ";
    return dbg.maybeSpace();
}
