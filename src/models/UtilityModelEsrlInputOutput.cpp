// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/UtilityModelEsrlInputOutput.h"
#include "util/To.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"
#include "util/UtilityTime.h"

const QString UtilityModelEsrlInputOutput::pattern1 = "<option selected>([0-9]{2} \\w{3} [0-9]{4} - [0-9]{2}Z)<.option>";
const QString UtilityModelEsrlInputOutput::pattern2 = "<option>([0-9]{2} \\w{3} [0-9]{4} - [0-9]{2}Z)<.option>";
const QString UtilityModelEsrlInputOutput::pattern3 = "[0-9]{2} \\w{3} ([0-9]{4}) - [0-9]{2}Z";
const QString UtilityModelEsrlInputOutput::pattern4 = "([0-9]{2}) \\w{3} [0-9]{4} - [0-9]{2}Z";
const QString UtilityModelEsrlInputOutput::pattern5 = "[0-9]{2} \\w{3} [0-9]{4} - ([0-9]{2})Z";
const QString UtilityModelEsrlInputOutput::pattern6 = "[0-9]{2} (\\w{3}) [0-9]{4} - [0-9]{2}Z";

RunTimeData UtilityModelEsrlInputOutput::getRunTime(ObjectModel * om) {
    RunTimeData runData;
    QString htmlRunStatus;
    if (om->model == "HRRR_AK") {
        htmlRunStatus = UtilityIO::getHtml(("https://rapidrefresh.noaa.gov/alaska/"));
    } else if (om->model == "RAP_NCEP") {
        htmlRunStatus = UtilityIO::getHtml(("https://rapidrefresh.noaa.gov/RAP/Welcome.cgi?dsKey=" + om->model.toLower() + "_jet&domain=full"));
    } else if (om->model == "RAP") {
        htmlRunStatus = UtilityIO::getHtml(("httpss://rapidrefresh.noaa.gov/RAP/"));
    } else if (om->model == "HRRR_NCEP") {
        htmlRunStatus = UtilityIO::getHtml(("https://rapidrefresh.noaa.gov/hrrr/HRRR/Welcome.cgi?dsKey=" + om->model.toLower() + "_jet&domain=full"));
    } else {
        htmlRunStatus = UtilityIO::getHtml(("https://rapidrefresh.noaa.gov/" + om->model.toLower() + "/" + om->model + "/Welcome.cgi?dsKey=" + om->model.toLower() + "_jet&domain=full"));
    }
    auto html = UtilityString::parse(htmlRunStatus, pattern1);
    const auto oldRunTimes = UtilityString::parseColumn(htmlRunStatus, pattern2);
    auto year = UtilityString::parse(html, pattern3);
    auto day = UtilityString::parse(html, pattern4);
    auto hour = UtilityString::parse(html, pattern5);
    auto monthStr = UtilityTime::monthWordToNumber(UtilityString::parse(html, pattern6));
    html = year + monthStr + day + hour;
    runData.appendListRun(html);
    runData.mostRecentRun = html;
    runData.imageCompleteInt = UtilityString::parseAndCount(htmlRunStatus, ".(allfields).") - 1;
    runData.imageCompleteStr = To::String(runData.imageCompleteInt);
    if (html != "") {
        for (auto index : UtilityList::range(13)) {
            year = UtilityString::parse(oldRunTimes[index], pattern3);
            day = UtilityString::parse(oldRunTimes[index], pattern4);
            hour = UtilityString::parse(oldRunTimes[index], pattern5);
            monthStr = UtilityTime::monthWordToNumber(UtilityString::parse(oldRunTimes[index], pattern6));
            runData.appendListRun(year + monthStr + day + hour);
        }
        runData.timeStringConversion = UtilityString::parse(html, "([0-9]{2})$");
    }
    return runData;
}

QString UtilityModelEsrlInputOutput::getImage(ObjectModel * om) {
    auto parentModel = om->model.replace("HRRR_AK", "alaska");
    if (om->model == "RAP_NCEP") {
        parentModel = "RAP";
    } else if (om->model == "HRRR_NCEP") {
        parentModel = "HRRR";
    }
    QString imgUrl = "";
    QString onDemandUrl = "";
    auto sectorLocal = om->sector.replace(" ", "");
    sectorLocal = sectorLocal.replace("Full", "full");
    sectorLocal = sectorLocal.replace("CONUS", "conus");
    auto param = om->param.replace("_full_", "_" + sectorLocal + "_");

    if (parentModel.contains("RAP")) {
        imgUrl = "https://rapidrefresh.noaa.gov/" + parentModel + "/for_web/" + om->model.toLower()
                + "_jet/" + om->run.replace("Z", "") + "/" + sectorLocal + "/" + param
                + "_f0" + om->timeStr.split(" ")[0] + ".png";
        onDemandUrl = "https://rapidrefresh.noaa.gov/" + parentModel + "/" + "displayMapUpdated"
                + ".cgi?keys=" + om->model.toLower() + "_jet:&runtime=" + om->run.replace("Z", "")
                + "&plot_type=" + param + "&fcst=" + om->timeStr.split(" ")[0]
                + "&time_inc=60&num_times=16&model=" + om->model.toLower() + "&ptitle=" + om->model
                + "%20Model%20Fields%20-%20Experimental&maxFcstLen=15&fcstStrLen=-1&domain="
                + sectorLocal + "&adtfn=1";
    } else {
        imgUrl = "https://rapidrefresh.noaa.gov/hrrr/" + parentModel.toUpper() + "/for_web/" + om->model.toLower()
                + "_jet/" + om->run.replace("Z", "") + "/" + sectorLocal + "/" + param + "_f0"
                + om->timeStr.split(" ")[0] + ".png";
        onDemandUrl = "https://rapidrefresh.noaa.gov/hrrr/" + parentModel.toUpper() + "/"
                + "displayMapUpdated" + ".cgi?keys=" + om->model.toLower()
                + "_jet:&runtime=" + om->run.replace("Z", "") + "&plot_type=" + param + "&fcst="
                + om->timeStr.split(" ")[0] + "&time_inc=60&num_times=16&model=" + om->model.toLower()
                + "&ptitle=" + om->model + "%20Model%20Fields%20-%20Experimental&maxFcstLen=15&fcstStrLen=-1&domain="
                + sectorLocal + "&adtfn=1";
    }
    UtilityIO::getHtml(onDemandUrl);
    return imgUrl;
}
