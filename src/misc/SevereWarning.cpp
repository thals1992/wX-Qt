// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/SevereWarning.h"
#include "objects/ObjectPolygonWarning.h"
#include "util/To.h"

SevereWarning::SevereWarning(PolygonType type)
    : type{ type }
{
    generateString();
}

string SevereWarning::getName() const {
    if (type == Tor) {
        return "Tornado Warning";
    } else if (type == Tst) {
        return "Severe Thunderstorm Warning";
    } else if (type == Ffw) {
        return "Flash Flood Warning";
    } else {
        return "";
    }
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

void SevereWarning::download() {
    ObjectPolygonWarning::polygonDataByType[type]->download();
    generateString();
}

void SevereWarning::generateString() {
    const auto html = ObjectPolygonWarning::polygonDataByType[type]->getData();
    warningList = ObjectWarning::parseJson(html);
}

string SevereWarning::getShortName() const {
    switch (type) {
        case Tor:
            return "TOR";
        case Tst:
            return "TST";
        case Ffw:
            return "FFW";
        default:
            return "";
    }
}
