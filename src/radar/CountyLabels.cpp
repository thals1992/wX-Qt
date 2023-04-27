// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/CountyLabels.h"
#include "common/GlobalVariables.h"
#include "objects/WString.h"
#include "util/To.h"
#include "util/UtilityIO.h"

bool CountyLabels::initialized{false};
vector<string> CountyLabels::names;
vector<LatLon> CountyLabels::location;

void CountyLabels::create() {
    if (!initialized) {
        initialized = true;
        const auto text = UtilityIO::readTextFile(GlobalVariables::resDir + "gaz_counties_national.txt");
        const auto lines = WString::split(text, GlobalVariables::newline);
        for (const auto& line : lines) {
            const auto items = WString::split(line, ",");
            names.push_back(items[1]);
            location.emplace_back(To::Double(items[2]), -1.0f * To::Double(items[3]));
        }
    }
}
