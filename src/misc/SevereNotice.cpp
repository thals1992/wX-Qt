// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "common/GlobalVariables.h"
#include "objects/ObjectPolygonWatch.h"
#include "misc/SevereNotice.h"
#include "util/To.h"

SevereNotice::SevereNotice() {
}

SevereNotice::SevereNotice(PolygonType type) {
    this->type = type;
}

void SevereNotice::getBitmaps() {
    QString noAlertsVerbiage;
    QString html;
    urls.clear();
    if (type == PolygonType::mcd) {
        noAlertsVerbiage = "No Mesoscale Discussions are currently in effect.";
        html = ObjectPolygonWatch::polygonDataByType[PolygonType::mcd]->numberList.getValue();
    } else if (type == PolygonType::watch) {
        noAlertsVerbiage = "No watches are currently valid";
        html = ObjectPolygonWatch::polygonDataByType[PolygonType::watch]->numberList.getValue();
    } else if (type == PolygonType::mpd) {
        noAlertsVerbiage = "No MPDs are currently in effect.";
        html = ObjectPolygonWatch::polygonDataByType[PolygonType::mpd]->numberList.getValue();
    } else {
        noAlertsVerbiage = "";
        html = "";
    }
    QString text = "";
    if (!html.contains(noAlertsVerbiage)) {
        text = html;
    } else {
        text = "";
    }
    auto numberList = text.split(":");
    if (text != "") {
        for (const auto& number : numberList) {
            if (number != "") {
                QString url;
                if (type == PolygonType::mcd) {
                    url = GlobalVariables::nwsSPCwebsitePrefix + "/products/md/mcd" + number + ".gif";
                } else if (type == PolygonType::watch) {
                    url = GlobalVariables::nwsSPCwebsitePrefix + "/products/watch/ww" + number + "_radar.gif";
                } else if (type == PolygonType::mpd) {
                    url = GlobalVariables::nwsWPCwebsitePrefix + "/metwatch/images/mcd" + number + ".gif";
                } else {
                    url = "";
                }
                urls.push_back(url);
            }
        }
    }
}

QString SevereNotice::getShortName() const {
    switch (type) {
        case PolygonType::mcd:
            return "MCD";
        case PolygonType::mpd:
            return "MPD";
        case PolygonType::watch:
            return "WATCH";
        default:
            return "";
    }
}

QString SevereNotice::getCount() const {
    return To::String(static_cast<int>(urls.size()));
}
