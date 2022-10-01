// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/UtilitySpc.h"
#include "common/GlobalVariables.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"

vector<string> UtilitySpc::getTstormOutlookUrls() {
    const auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/products/exper/enhtstm/");
    const auto imageNames = UtilityString::parseColumn(html, "OnClick.\"show_tab\\(.([0-9]{4}).\\)\".*?");
    vector<string> urls;
    for (const auto& imageName : imageNames) {
        urls.push_back(GlobalVariables::nwsSPCwebsitePrefix + "/products/exper/enhtstm/imgs/enh_" + imageName + ".gif");
    }
    return urls;
}
