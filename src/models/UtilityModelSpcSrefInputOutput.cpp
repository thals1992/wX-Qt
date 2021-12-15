// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/UtilityModelSpcSrefInputOutput.h"
#include "common/GlobalVariables.h"
#include "models/RunTimeData.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"

QString UtilityModelSpcSrefInputOutput::pattern1 = "([0-9]{10}z</a>&nbsp in through <b>f[0-9]{3})";
QString UtilityModelSpcSrefInputOutput::pattern2 = "<tr><td class=.previous.><a href=sref.php\\?run=[0-9]{10}&id=SREF_H5__>([0-9]{10}z)</a></td></tr>";

RunTimeData UtilityModelSpcSrefInputOutput::getRunTime() {
    RunTimeData runData;
    auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/exper/sref/");
    auto tmpTxt = UtilityString::parse(html, pattern1);
    auto results = UtilityString::parseColumn(html, pattern2);
    auto latestRun = tmpTxt.split("</a>")[0];
    runData.appendListRun(latestRun.replace("z", ""));
    for (auto result : results) {
        runData.appendListRun(result.replace("z", ""));
    }
    tmpTxt = UtilityString::parse(tmpTxt, pattern1);
    tmpTxt = UtilityString::parse(tmpTxt, "(f[0-9]{3})");
    runData.imageCompleteStr = tmpTxt;
    if (runData.listRun.size() > 0) {
        runData.mostRecentRun = runData.listRun[0];
    }
    return runData;
}

QString UtilityModelSpcSrefInputOutput::getImage(ObjectModel * om) {
    auto imgUrl = GlobalVariables::nwsSPCwebsitePrefix + "/exper/sref/gifs/" + om->run.replace("z", "") + "/" + om->param + "f0" + om->timeStr.split(" ")[0] + ".gif";
    return imgUrl;
}
