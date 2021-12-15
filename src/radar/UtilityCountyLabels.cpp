// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityCountyLabels.h"
#include "common/GlobalVariables.h"
#include "util/To.h"
#include "util/UtilityIO.h"

bool UtilityCountyLabels::initialized = false;
QStringList UtilityCountyLabels::names;
QVector<LatLon> UtilityCountyLabels::location;

void UtilityCountyLabels::create() {
    if (!initialized) {
        initialized = true;
        const auto text = UtilityIO::readTextFile(GlobalVariables::resDir + "gaz_counties_national.txt");
        auto lines = text.split(GlobalVariables::newline);
        lines.removeLast();
        for (const auto& line : lines) {
            const auto items = line.split(",");
            names.push_back(items[1]);
            location.push_back(LatLon(To::Float(items[2]), -1.0f * To::Float(items[3])));
        }
    }
}
