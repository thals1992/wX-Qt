// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/UtilitySpc.h"
#include <QString>
#include "common/GlobalVariables.h"
#include "util/UtilityIO.h"
#include "util/UtilityString.h"

QStringList UtilitySpc::getTstormOutlookUrls() {
    const auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/products/exper/enhtstm/");
    const auto imageNames = UtilityString::parseColumn(html, "OnClick.\"show_tab\\(.([0-9]{4}).\\)\".*?");
    QStringList urls;
    for (const auto& imageName : imageNames) {
        urls.push_back(GlobalVariables::nwsSPCwebsitePrefix + "/products/exper/enhtstm/imgs/enh_" + imageName + ".gif");
    }
    return urls;
}
