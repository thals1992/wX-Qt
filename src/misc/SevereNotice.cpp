// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "common/GlobalVariables.h"
#include "objects/PolygonWatch.h"
#include "objects/WString.h"
#include "misc/SevereNotice.h"
#include "util/To.h"

SevereNotice::SevereNotice(PolygonType type)
    : type{ type }
{}

void SevereNotice::getBitmaps() {
    string noAlertsVerbiage;
    string html;
    urls.clear();
    if (type == Mcd) {
        noAlertsVerbiage = "No Mesoscale Discussions are currently in effect.";
        html = PolygonWatch::byType[Mcd]->numberList.getValue();
    } else if (type == Watch) {
        noAlertsVerbiage = "No watches are currently valid";
        html = PolygonWatch::byType[Watch]->numberList.getValue();
    } else if (type == Mpd) {
        noAlertsVerbiage = "No MPDs are currently in effect.";
        html = PolygonWatch::byType[Mpd]->numberList.getValue();
    }
    string text;
    if (!WString::contains(html, noAlertsVerbiage)) {
        text = html;
    }
    auto numberList = WString::split(text, ":");
    if (!text.empty()) {
        for (const auto& number : numberList) {
            if (!number.empty()) {
                string url;
                if (type == Mcd) {
                    url = GlobalVariables::nwsSPCwebsitePrefix + "/products/md/mcd" + number + ".png";
                } else if (type == Watch) {
                    url = GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/ww" + number + "_radar.gif";
                } else if (type == Mpd) {
                    url = GlobalVariables::nwsWPCwebsitePrefix + "/metwatch/images/mcd" + number + ".gif";
                }
                urls.push_back(url);
            }
        }
    }
}

string SevereNotice::getShortName() const {
    return WString::toUpper(PolygonWatch::namesByEnumId.at(type));
}

string SevereNotice::getCount() const {
    return To::string(static_cast<int>(urls.size()));
}

int SevereNotice::getCountAsInt() const {
    return static_cast<int>(urls.size());
}
