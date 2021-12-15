// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/UtilityModelSpcHrrrInputOutput.h"
#include "common/GlobalVariables.h"
#include "models/RunTimeData.h"
#include "models/UtilityModelSpcHrrrInterface.h"
#include "util/To.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

RunTimeData UtilityModelSpcHrrrInputOutput::getRunTime() {
    RunTimeData runData;
    auto htmlRunStatus = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/exper/hrrr/data/hrrr3/cron.log");
    runData.validTime = UtilityString::parse(htmlRunStatus, "Latest Run: ([0-9]{10})");
    runData.mostRecentRun = runData.validTime;
    runData.appendListRun(runData.mostRecentRun);
    auto runTimes = UtilityString::parseColumn(htmlRunStatus, "Run: ([0-9]{8}/[0-9]{4})");
    for (auto time : UtilityList::reversed(runTimes)) {
        auto t = time.replace("/", "");
        if (t != (runData.mostRecentRun + "00")) {
            t.chop(2);
            runData.appendListRun(t);
        }
    }
    return runData;
}

QString UtilityModelSpcHrrrInputOutput::getImage(ObjectModel * om) {
    auto time = om->timeStr.split(" ")[0];
    auto imgUrl = GlobalVariables::nwsSPCwebsitePrefix + "/exper/hrrr/data/hrrr3/" + getSectorCode(om->sector).toLower() + "/R" + om->run.replace("Z", "") + "_F" + formatTime(time) + "_V" + getValidTime(om->run, om->timeStr, om->runTimeData.validTime) + "_" + getSectorCode(om->sector) + "_" + om->param + ".gif";
    return imgUrl;
}

QString UtilityModelSpcHrrrInputOutput::getSectorCode(const QString& sectorName) {
    QString sectorCode = "S19";
    for (auto index : UtilityList::range(UtilityModelSpcHrrrInterface::sectors.size())) {
        if (sectorName == UtilityModelSpcHrrrInterface::sectors[index]) {
            sectorCode = UtilityModelSpcHrrrInterface::sectorCodes[index];
            break;
        }
    }
    return sectorCode;
}

QString UtilityModelSpcHrrrInputOutput::getValidTime(const QString& run, const QString& validTimeForecast, const QString& validTime) {
    QString validTimeCurrent;
    if (run.size() == 10 && validTime.size() == 10) {
        auto runTimePrefix = UtilityString::substring(run, 0, 8);
        auto runTimeHr = UtilityString::substring(run, 8, 10);
        auto endTimePrefix = UtilityString::substring(validTime, 0, 8);
        auto runTimeHrInt = To::Int(runTimeHr);
        auto forecastInt = To::Int(validTimeForecast.split(" ")[0]);
        if ((runTimeHrInt + forecastInt) > 23) {
            validTimeCurrent = endTimePrefix + To::String(runTimeHrInt + forecastInt - 24).rightJustified(2, '0');
        } else {
            validTimeCurrent = runTimePrefix + To::String(runTimeHrInt + forecastInt).rightJustified(2, '0');
        }
    }
    return validTimeCurrent;
}

QString UtilityModelSpcHrrrInputOutput::formatTime(const QString& timeString) {
    return "0" + timeString;
}
