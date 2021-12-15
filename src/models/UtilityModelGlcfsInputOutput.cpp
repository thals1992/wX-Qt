// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/UtilityModelGlcfsInputOutput.h"
#include "util/UtilityString.h"

QString UtilityModelGlcfsInputOutput::getImage(ObjectModel * om) {
    auto sectorLocal = om->sector;
    if (om->sector.split(" ").size() > 1) {
        sectorLocal = UtilityString::substring(om->sector.split(" ")[1], 0, 1).toLower();
    }
    auto url = "https://www.glerl.noaa.gov/res/glcfs/fcast/" + sectorLocal + om->param + "+" + om->timeStr + ".gif";
    return url;
}
