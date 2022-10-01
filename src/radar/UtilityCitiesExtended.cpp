// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityCitiesExtended.h"
#include "common/GlobalVariables.h"
#include "objects/WString.h"
#include "util/To.h"
#include "util/UtilityIO.h"

bool UtilityCitiesExtended::initialized{false};
vector<CityExt> UtilityCitiesExtended::cities;

void UtilityCitiesExtended::create() {
    if (!initialized) {
        initialized = true;
        const auto text = UtilityIO::readTextFile(GlobalVariables::resDir + "cityall.txt");
        const auto lines = WString::split(text, GlobalVariables::newline);
        for (const auto& line : lines) {
            const auto items = WString::split(line, ",");
            if (items.size() > 2) {
                cities.emplace_back(items[0], To::Double(items[1]), -1.0f * To::Double(items[2]));
            }
        }
    }
}
