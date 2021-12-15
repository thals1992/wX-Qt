// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/UtilityModels.h"
#include <cstdint>
#include "util/To.h"
#include "util/UtilityTime.h"

QString UtilityModels::convertTimeRuntoTimeString(QString runStr, QString timeStrFunc) {
    auto timeStr = timeStrFunc.split(" ")[0];
    const auto runInt = To::Int(runStr);
    const auto timeInt = To::Int(timeStr);
    const int realTimeGmt = runInt + timeInt;
    const int64_t offsetFromUtc = UtilityTime::secondsFromUTC();
    const int realTime = realTimeGmt + static_cast<int>(offsetFromUtc / 60 / 60);
    int hourOfDay = realTime % 24;
    QString amPm;
    if (hourOfDay > 11) {
        amPm = "pm";
        if (hourOfDay > 12) {
            hourOfDay -= 12;
        }
    } else {
        amPm = "am";
    }
    double day = realTime / 24;
    if (hourOfDay < 0) {
        hourOfDay = 12 + hourOfDay;
        amPm = "pm";
        day -= 1;
    }
    const auto localTime = QDate::currentDate();
    const auto dayOfWeek = localTime.dayOfWeek();
    QString futureDay;
    auto dayMod = static_cast<int>(dayOfWeek + day) % 7;
    if (dayMod == 0) {
        dayMod = 7;
    }
    switch (dayMod) {
        case 1:
            futureDay = "Mon";
            break;
        case 2:
            futureDay = "Tue";
            break;
        case 3:
            futureDay = "Wed";
            break;
        case 4:
            futureDay = "Thu";
            break;
        case 5:
            futureDay = "Fri";
            break;
        case 6:
            futureDay = "Sat";
            break;
        case 7:
            futureDay = "Sun";
            break;
        default:
            futureDay = "";
            break;
    }
    auto returnString = futureDay + " " + To::String(hourOfDay) + amPm;
    return returnString;
}

QStringList UtilityModels::updateTime(QString run, QString modelCurrentTime, QStringList listTime, QString prefix) {
    auto run2 = run;
    run2 = run2.replace("Z", "");
    run2 = run2.replace("z", "");
    QStringList listTimeNew;
    auto modelCurrentTime2 = modelCurrentTime;
    modelCurrentTime2 = modelCurrentTime2.replace("Z", "");
    modelCurrentTime2 = modelCurrentTime2.replace("z", "");
    if (modelCurrentTime2 != "") {
        if (To::Int(run2) > To::Int(modelCurrentTime2)) {
            run2 = To::String(To::Int(run2) - 24);
        }
        for (const QString& value : listTime) {
            const auto tmpStr = value.split(" ")[0].replace(prefix, "");
            listTimeNew.push_back(prefix + tmpStr + " " + convertTimeRuntoTimeString(run2, tmpStr));
        }
    }
    return listTimeNew;
}
