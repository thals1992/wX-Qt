// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "UtilitySpcMesoInputOutput.h"
#include <iostream>
#include "../common/GlobalVariables.h"
#include "../objects/WString.h"
#include "../util/UtilityIO.h"
#include "../util/UtilityString.h"

vector<string> UtilitySpcMesoInputOutput::getAnimation(const string& product, const string& sector, size_t frameCount) {
    vector<string> urls;
    auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/exper/mesoanalysis/new/archiveviewer.php?sector=19&parm=pmsl");
    html = WString::replace(html, "\n", " ");
    const auto timeList = UtilityString::parseColumn(html, "dattim\\[[0-9]{1,2}\\].*?=.*?([0-9]{8})");
    if (timeList.size() > frameCount) {
        for (int index = frameCount - 1; index >= 0; index -= 1) {
            const auto imgUrl = GlobalVariables::nwsSPCwebsitePrefix + "/exper/mesoanalysis/s" + sector + "/" + product + "/" + product + "_" + timeList[index] + ".gif";
            urls.push_back(imgUrl);
        }
    }
    return urls;
}
