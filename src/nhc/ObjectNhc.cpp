// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/ObjectNhc.h"
#include "common/GlobalVariables.h"
#include "util/DownloadText.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

void ObjectNhc::getTextData() {
    statusList.clear();

    const auto url = GlobalVariables::nwsNhcWebsitePrefix + "/CurrentStorms.json";
    // const string url = "https://www.nhc.noaa.gov/productexamples/NHC_JSON_Sample.json";

    const auto html = UtilityIO::getHtml(url);
    ids = UtilityString::parseColumn(html, "\"id\": \"(.*?)\"");
    binNumbers = UtilityString::parseColumn(html, "\"binNumber\": \"(.*?)\"");
    names = UtilityString::parseColumn(html, "\"name\": \"(.*?)\"");
    classifications = UtilityString::parseColumn(html, "\"classification\": \"(.*?)\"");

    intensities = UtilityString::parseColumn(html, "\"intensity\": \"(.*?)\"");
    pressures = UtilityString::parseColumn(html, "\"pressure\": \"(.*?)\"");
    // sample data not quoted for these two;
    // intensities = UtilityString::parseColumn(html, "\"intensity\": (.*?),");
    // pressures = UtilityString::parseColumn(html, "\"pressure\": (.*?),");

    latitudes = UtilityString::parseColumn(html, "\"latitude\": \"(.*?)\"");
    longitudes = UtilityString::parseColumn(html, "\"longitude\": \"(.*?)\"");
    movementDirs = UtilityString::parseColumn(html, "\"movementDir\": (.*?),");
    movementSpeeds = UtilityString::parseColumn(html, "\"movementSpeed\": (.*?),");
    lastUpdates = UtilityString::parseColumn(html, "\"lastUpdate\": \"(.*?)\"");
    for (const auto& bin : binNumbers) {
        const auto text = DownloadText::byProduct("MIATCP" + bin);
        const auto status = UtilityString::parse(text, "(\\.\\.\\..*?\\.\\.\\.)");
        statusList.push_back(status);
    }
}

void ObjectNhc::showTextData() {
    if (!ids.empty()) {
        for (auto index : range(ids.size())) {
            stormDataList.emplace_back(
                names[index],
                movementDirs[index],
                movementSpeeds[index],
                pressures[index],
                binNumbers[index],
                ids[index],
                lastUpdates[index],
                classifications[index],
                latitudes[index],
                longitudes[index],
                intensities[index],
                statusList[index]);
        }
    }
}
