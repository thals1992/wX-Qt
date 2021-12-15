// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UtilityCitiesExtended.h"
#include "common/GlobalVariables.h"
#include "util/To.h"
#include "util/UtilityIO.h"

bool UtilityCitiesExtended::initialized = false;
QVector<CityExt> UtilityCitiesExtended::cities;

void UtilityCitiesExtended::create() {
    if (!initialized) {
        initialized = true;
        const auto text = UtilityIO::readTextFile(GlobalVariables::resDir + "cityall.txt");
        auto lines = text.split(GlobalVariables::newline);
        lines.removeLast();
        for (const auto& line : lines) {
            const auto items = line.split(",");
            if (items.size() > 2) {
                cities.push_back(CityExt(items[0], To::Float(items[1]), -1.0f * To::Float(items[2])));
            }
        }
    }
}
