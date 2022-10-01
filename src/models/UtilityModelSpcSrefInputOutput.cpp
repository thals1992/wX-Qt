// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "UtilityModelSpcSrefInputOutput.h"
#include "../common/GlobalVariables.h"
#include "../objects/WString.h"
#include "../util/UtilityIO.h"
#include "../util/UtilityString.h"

const string UtilityModelSpcSrefInputOutput::srefPattern2{"([0-9]{10}z</a>&nbsp in through <b>f[0-9]{3})"};
const string UtilityModelSpcSrefInputOutput::srefPattern3{"<tr><td class=.previous.><a href=sref.php\\?run=[0-9]{10}&id=SREF_H5__>([0-9]{10}z)</a></td></tr>"};

RunTimeData UtilityModelSpcSrefInputOutput::getRunTime() {
    auto runData = RunTimeData{};
    auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/exper/sref/");
    auto tmpTxt = UtilityString::parse(html, srefPattern2);
    auto result = UtilityString::parseColumn(html, srefPattern3);
    auto latestRun = WString::split(tmpTxt, "</a>")[0];
    runData.appendListRun(WString::replace(latestRun, "z", ""));
    if (!result.empty()) {
        for (const auto& data : result) {
            runData.appendListRun(WString::replace(data, "z", ""));
        }
    }
//    tmpTxt = UtilityString::parse(tmpTxt, srefPattern2);
//    tmpTxt = UtilityString::parse(tmpTxt, "(f[0-9]{3})");
    if (!runData.listRun.empty()) {
        runData.mostRecentRun = runData.listRun[0];
    }
    return runData;
}

string UtilityModelSpcSrefInputOutput::getImageUrl(ObjectModel * om) {
    return GlobalVariables::nwsSPCwebsitePrefix + "/exper/sref/gifs/" + WString::replace(om->run, "z", "") + "/" + om->param + "f" + om->getTime() + ".gif";
}
