// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/UtilityModelSpcHrefInputOutput.h"
#include "common/GlobalVariables.h"
#include "models/UtilityModelSpcHrefInterface.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"
#include "util/UtilityTime.h"

RunTimeData UtilityModelSpcHrefInputOutput::getRunTime() {
    RunTimeData runData;
    auto htmlRunStatus = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/exper/href/");
    auto html = UtilityString::parse(htmlRunStatus, "\\{model: \"href\",product: \"500mb_mean\",sector: \"conus\",(rd: .[0-9]{8}\",rt: .[0-9]{4}\",\\})");
    auto day = UtilityString::parse(html, "rd:.(.*?),.*?").replace("\"", "");
    auto time = UtilityString::parse(html, "rt:.(.*?)00.,.*?").replace("\"", "");
    auto mostRecentRun = day + time;
    runData.appendListRun(mostRecentRun);
    runData.appendListRun(UtilityTime::genModelRuns(mostRecentRun, 12, "yyyyMMddHH"));
    runData.mostRecentRun = mostRecentRun;
    return runData;
}

QStringList UtilityModelSpcHrefInputOutput::getImage(ObjectModel * om) {
    auto year = UtilityString::substring(om->run, 0, 4);
    auto month = UtilityString::substring(om->run, 4, 6);
    auto day = UtilityString::substring(om->run, 6, 8);
    auto hour = UtilityString::substring(om->run, 8, 10);
    auto products = om->param.split(",");
    QStringList urls = {GlobalVariables::nwsSPCwebsitePrefix + "/exper/href/graphics/spc_white_1050px.png"};
    urls.push_back(GlobalVariables::nwsSPCwebsitePrefix + "/exper/href/graphics/noaa_overlay_1050px.png");
    auto sectorIndex = UtilityModelSpcHrefInterface::sectorsLong.indexOf(om->sector);
    auto sector = UtilityModelSpcHrefInterface::sectors[sectorIndex];
    for (const auto& product : products) {
        QString url = "";
        if (product.contains("cref_members")) {
            auto paramArr = product.split(" ");
            url = GlobalVariables::nwsSPCwebsitePrefix + "/exper/href/graphics/models/href/" + year + "/" + month + "/" + day + "/" + hour + "00/f0" + om->timeStr + "00/" + paramArr[0] + "." + sector + ".f0" + om->timeStr + "00." + paramArr[1] + ".tl00.png";
        } else {
            url = GlobalVariables::nwsSPCwebsitePrefix + "/exper/href/graphics/models/href/" + year + "/" + month + "/" + day + "/" + hour + "00/f0" + om->timeStr + "00/" + product + "." + sector + ".f0" + om->timeStr + "00.png";
        }
        urls.push_back(url);
    }
    urls.push_back(GlobalVariables::nwsSPCwebsitePrefix + "/exper/href/graphics/blank_maps/" + sector + ".png");
    return urls;
}
