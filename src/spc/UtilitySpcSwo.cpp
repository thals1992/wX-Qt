// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "spc/UtilitySpcSwo.h"
#include <QString>
#include <QStringList>
#include "common/GlobalVariables.h"
#include "util/To.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

QString UtilitySpcSwo::getImageUrlsDays48(const QString& day) {
    return GlobalVariables::nwsSPCwebsitePrefix + "/products/exper/day4-8/day" + day + "prob.gif";
}

QStringList UtilitySpcSwo::getImageUrls(const QString& day) {
    QStringList urls;
    if (day == "48") {
        for (auto dayInt : UtilityList::range2(4, 9)) {
            urls.push_back(GlobalVariables::nwsSPCwebsitePrefix + "/products/exper/day4-8/day" + To::String(dayInt) + "prob.gif");
        }
        return urls;
    }
    const auto html = UtilityIO::getHtml(GlobalVariables::nwsSPCwebsitePrefix + "/products/outlook/day" + day + "otlk.html");
    const auto time = UtilityString::parse(html, "show_tab\\(.otlk_([0-9]{4}).\\)");
    if (day == "1" || day == "2") {
        auto baseUrl = GlobalVariables::nwsSPCwebsitePrefix + "/products/outlook/day" + day + "probotlk_";
        urls.push_back(GlobalVariables::nwsSPCwebsitePrefix + "/products/outlook/day" + day + "otlk_" + time + ".gif");
        const QStringList day1Urls = {"_torn.gif", "_hail.gif", "_wind.gif"};
        for (const auto& urlEnd : day1Urls) {
            urls.push_back(baseUrl + time + urlEnd);
        }
    } else {
        const QStringList day3Urls = {"otlk_", "prob_"};
        for (const auto& urlEnd : day3Urls) {
            urls.push_back(GlobalVariables::nwsSPCwebsitePrefix + "/products/outlook/day" + day + urlEnd + time + ".gif");
        }
    }
    return urls;
}
