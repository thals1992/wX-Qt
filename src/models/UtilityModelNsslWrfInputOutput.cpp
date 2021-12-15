// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/UtilityModelNsslWrfInputOutput.h"
#include "models/UtilityModelNsslWrfInterface.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"
#include "util/UtilityTime.h"

const QString UtilityModelNsslWrfInputOutput::baseUrl = "https://cams.nssl.noaa.gov";

RunTimeData UtilityModelNsslWrfInputOutput::getRunTime(ObjectModel * om) {
    RunTimeData runData;
    QString modelCode;
    if (om->model == "WRF") {
        modelCode = "wrf_nssl";
    } else if (om->model == "WRF_3KM") {
        modelCode = "wrf_nssl_3km";
    } else if (om->model == "HRRRV3") {
        modelCode = "hrrrv3";
    } else if (om->model == "FV3") {
        modelCode = "fv3_nssl";
    }
    auto htmlRunStatus = UtilityIO::getHtml(baseUrl + "/?model=" + modelCode);
    auto html = UtilityString::parse(htmlRunStatus, "\\{model: \"" + modelCode + "\",(rd: .[0-9]{8}\",rt: .[0-9]{4}\",)");
    auto day = UtilityString::parse(html, "rd:.(.*?),.*?").replace("\"", "");
    auto time = UtilityString::parse(html, "rt:.(.*?)00.,.*?").replace("\"", "");
    auto mostRecentRun = day + time;
    runData.appendListRun(mostRecentRun);
    runData.appendListRun(UtilityTime::genModelRuns(mostRecentRun, 12, "yyyyMMddHH"));
    runData.mostRecentRun = mostRecentRun;
    return runData;
}

QStringList UtilityModelNsslWrfInputOutput::getImage(ObjectModel * om) {
    auto sectorIndex = UtilityModelNsslWrfInterface::sectorsLong.indexOf(om->sector);
    auto sector = UtilityModelNsslWrfInterface::sectors[sectorIndex];
    auto baseLayerUrl = "https://cams.nssl.noaa.gov/graphics/blank_maps/spc_" + sector + ".png";
    QString modelPostfix = "_nssl";
    auto model = om->model.toLower();
    if (om->model == "HRRRV3") {
        modelPostfix = "";
    }
    if (om->model == "WRF_3KM") {
        model = "wrf_nssl_3km";
        modelPostfix = "";
    }
    auto year = UtilityString::substring(om->run, 0, 4);
    auto month = UtilityString::substring(om->run, 4, 6);
    auto day = UtilityString::substring(om->run, 6, 8);
    auto hour = UtilityString::substring(om->run, 8, 10);
    auto url = baseUrl + "/graphics/models/" + model + modelPostfix + "/" + year + "/" + month + "/" + day + "/" + hour + "00/f0" + om->timeStr.split(" ")[0] + "00/" + om->param + ".spc_" + sector.toLower() + ".f0" + om->timeStr.split(" ")[0] + "00.png";
    return {baseLayerUrl, url};
}
