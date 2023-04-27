// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/SevereWarning.h"
#include "objects/PolygonWarning.h"
#include "util/To.h"

SevereWarning::SevereWarning(PolygonType type)
    : type{ type }
{
    generateString();
}

string SevereWarning::getCount() const {
    auto i = 0;
    for (const auto& s : warningList) {
        if (s.isCurrent) {
            i += 1;
        }
    }
    return To::string(i);
}

int SevereWarning::getCountAsInt() const {
    auto i = 0;
    for (const auto& s : warningList) {
        if (s.isCurrent) {
            i += 1;
        }
    }
    return i;
}

void SevereWarning::download() {
    PolygonWarning::byType[type]->download();
    generateString();
}

void SevereWarning::generateString() {
    const auto html = PolygonWarning::byType[type]->getData();
    warningList = ObjectWarning::parseJson(html);
}

string SevereWarning::getName() const {
    // if (type == Tor) {
    //     return "Tornado Warning";
    // } else if (type == Tst) {
    //     return "Severe Thunderstorm Warning";
    // } else if (type == Ffw) {
    //     return "Flash Flood Warning";
    // } else {
    //     return "";
    // }
    return PolygonWarning::getLongName(type);
}

string SevereWarning::getShortName() const {
    // switch (type) {
    //     case Tor:
    //         return "TOR";
    //     case Tst:
    //         return "TST";
    //     case Ffw:
    //         return "FFW";
    //     default:
    //         return "";
    // }
    return PolygonWarning::getShortName(type);
}
