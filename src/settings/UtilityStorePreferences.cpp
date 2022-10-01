// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/UtilityStorePreferences.h"
#include "util/Utility.h"

void UtilityStorePreferences::setDefaults() {
    Utility::writePref("RADAR_SHOW_COUNTY", "true");
    Utility::writePref("LOC_NUM_INT",  "1");
    Utility::writePref("LOC1_X", "35.231");
    Utility::writePref("LOC1_Y", "-97.451");
    Utility::writePref("LOC1_NWS", "OUN");
    Utility::writePref("LOC1_LABEL", "home");
    Utility::writePref("NWS1", "OUN");
    Utility::writePref("RID1", "TLX");
    Utility::writePref("CURRENT_LOC_FRAGMENT", "1");
}
