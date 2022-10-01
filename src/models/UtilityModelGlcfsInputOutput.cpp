// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "UtilityModelGlcfsInputOutput.h"
#include "../objects/WString.h"
#include "../util/UtilityString.h"

string UtilityModelGlcfsInputOutput::getImageUrl(ObjectModel * om) {
    auto sectorLocal = om->sector;
    if (WString::split(om->sector, " ").size() > 1) {
        auto tmp = WString::split(om->sector, " ")[1];
        tmp = UtilityString::substring(tmp, 0, 1);
        tmp = WString::toLower(tmp);
        sectorLocal = tmp;
    }
    return "https://www.glerl.noaa.gov/res/glcfs/fcast/" + sectorLocal + om->param + "+" + om->getTime() + ".gif";
}
