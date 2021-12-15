// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/UtilityModelNcepInputOutput.h"
#include "models/RunTimeData.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"

const QString UtilityModelNcepInputOutput::pattern = "current_cycle_white . .([0-9 ]{11} UTC)";

RunTimeData UtilityModelNcepInputOutput::getRunTime(ObjectModel * om) {
    RunTimeData runData;
    const auto url = "https://mag.ncep.noaa.gov/model-guidance-model-parameter.php?group=Model%20Guidance&model=" + om->model.toUpper() + "&area=" + om->sector + "&ps=area";
    auto html = UtilityIO::getHtml(url);
    html = UtilityString::parse(html, pattern).replace("UTC", "Z").replace(" ", "");
    auto htmlTmp = html;
    auto runCompletionDataStr = htmlTmp.replace("Z", " UTC");
    if (runCompletionDataStr != "") {
        runCompletionDataStr = UtilityString::insert(runCompletionDataStr, 8, " ");
    }
    // QString runCompletionUrl = "https://mag.ncep.noaa.gov/model-guidance-model-parameter.php?group=Model%20Guidance&model=" + om->model.toUpper();
    // runCompletionUrl += "&area=" + om->sector.toLower();
    // runCompletionUrl += "&cycle=" + runCompletionDataStr;
    // runCompletionUrl += "&param=" + om->param + "&fourpan=no&imageSize=M&ps=area";
    // runCompletionUrl = runCompletionUrl.replace(" ", "%20");
    const QString ncepPattern1 = "([0-9]{2}Z)";
    const auto time = UtilityString::parse(html, ncepPattern1);
    runData.mostRecentRun = time;
    runData.timeStringConversion = time;
    auto timeCompleteUrl = "https://mag.ncep.noaa.gov/model-fhrs.php?group=Model%20Guidance&model=" + om->model.toLower() + "&fhr_mode=image&loop_start=-1&loop_end=-1&area=" + om->sector + "&fourpan=no&imageSize=&preselected_formatted_cycle_date=" + runCompletionDataStr + "&cycle=" + runCompletionDataStr + "&param=" + om->param + "&ps=area";
    const auto timeCompleteHtml = UtilityIO::getHtml(timeCompleteUrl.replace(" ", "%20"));
    runData.imageCompleteStr = UtilityString::parse(timeCompleteHtml, "SubmitImageForm.(.*?).\"");
    return runData;
}

QString UtilityModelNcepInputOutput::getImage(ObjectModel * om) {
    QString imgUrl;
    auto timeLocal = om->timeStr;
    auto runTmp = om->run;
    if (om->model == "HRRR") {
        timeLocal = om->timeStr + "00";
    }
    if (om->model == "GFS") {
        imgUrl = "https://mag.ncep.noaa.gov/data/" + om->model.toLower() + "/" + runTmp.replace("Z", "") + "/" + om->sector.toLower() + "/" + om->param + "/" + om->model.toLower() + "_" + om->sector.toLower() + "_" + timeLocal + "_" + om->param + ".gif";
    } else {
        imgUrl = "https://mag.ncep.noaa.gov/data/" + om->model.toLower() + "/" + runTmp.replace("Z", "") + "/" + om->model.toLower() + "_" + om->sector.toLower() + "_" + timeLocal + "_" + om->param + ".gif";
    }
    return imgUrl;
}
