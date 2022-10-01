// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/UtilitySpcSwo.h"
#include "common/GlobalVariables.h"
#include "util/To.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

string UtilitySpcSwo::getImageUrlsDays48(const string& day) {
    return GlobalVariables::nwsSPCwebsitePrefix + "/products/exper/day4-8/day" + day + "prob.gif";
}

vector<string> UtilitySpcSwo::getImageUrls(const string& day) {
    vector<string> urls;
    if (day == "48") {
        for (auto dayInt : range2(4, 9)) {
            urls.push_back(GlobalVariables::nwsSPCwebsitePrefix + "/products/exper/day4-8/day" + To::string(dayInt) + "prob.gif");
        }
        return urls;
    }
    const auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/products/outlook/day" + day + "otlk.html");
    const auto time = UtilityString::parse(html, "show_tab\\(.otlk_([0-9]{4}).\\)");
    if (day == "1" || day == "2") {
        auto baseUrl = GlobalVariables::nwsSPCwebsitePrefix + "/products/outlook/day" + day + "probotlk_";
        urls.push_back(GlobalVariables::nwsSPCwebsitePrefix + "/products/outlook/day" + day + "otlk_" + time + ".gif");
        for (const auto& urlEnd : {"_torn.gif", "_hail.gif", "_wind.gif"}) {
            urls.push_back(baseUrl + time + urlEnd);
        }
    } else {
        for (const auto& urlEnd : {"otlk_", "prob_"}) {
            urls.push_back(GlobalVariables::nwsSPCwebsitePrefix + "/products/outlook/day" + day + urlEnd + time + ".gif");
        }
    }
    return urls;
}
