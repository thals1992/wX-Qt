// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/UtilityModelWpcGefsInputOutput.h"
#include "common/GlobalVariables.h"
#include "models/RunTimeData.h"
#include "util/UtilityTime.h"

RunTimeData UtilityModelWpcGefsInputOutput::getRunTime() {
    auto runData = RunTimeData();
    auto currentHour = UtilityTime::getCurrentHourInUTC();
    runData.mostRecentRun = "00";
    if (currentHour >= 12 && currentHour < 18) {
        runData.mostRecentRun = "06";
    }
    if (currentHour >= 18) {
        runData.mostRecentRun = "12";
    }
    if (currentHour < 6) {
        runData.mostRecentRun = "18";
    }
    runData.listRun << "00" << "06" << "12" << "18";
    runData.timeStringConversion = runData.mostRecentRun;
    return runData;
}

QString UtilityModelWpcGefsInputOutput::getImage(ObjectModel * om) {
    QString sectorAdd = "";
    if (om->sector == "AK") {
        sectorAdd = "_ak";
    }
    auto url = GlobalVariables::nwsWPCwebsitePrefix + "/exper/gefs/" + om->run + "/GEFS_" + om->param + "_" + om->run + "Z_f" + om->timeStr.split(" ")[0] + sectorAdd + ".gif";
    return url;
}
