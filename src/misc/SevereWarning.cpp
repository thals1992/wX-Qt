// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/SevereWarning.h"
#include "objects/ObjectPolygonWarning.h"
#include "util/To.h"

SevereWarning::SevereWarning() {
}

SevereWarning::SevereWarning(PolygonType type) {
    this->type = type;
    generateString();
}

QString SevereWarning::getName() const {
    if (type == PolygonType::tor) {
        return "Tornado Warning";
    } else if (type == PolygonType::tst) {
        return "Severe Thunderstorm Warning";
    } else if (type == PolygonType::ffw) {
        return "Flash Flood Warning";
    } else {
        return "";
    }
}

QString SevereWarning::getCount() const {
    auto i = 0;
    for (const auto& s : warningList) {
        if (s.isCurrent) {
            i += 1;
        }
    }
    return To::String(i);
}

void SevereWarning::download() {
    ObjectPolygonWarning::polygonDataByType[type]->download();
    generateString();
}

void SevereWarning::generateString() {
    auto html = ObjectPolygonWarning::polygonDataByType[type]->getData();
    warningList = ObjectWarning::parseJson(html);
}

QString SevereWarning::getShortName() const {
    switch (type) {
        case PolygonType::tor:
            return "TOR";
        case PolygonType::tst:
            return "TST";
        case PolygonType::ffw:
            return "FFW";
        default:
            return "";
    }
}
