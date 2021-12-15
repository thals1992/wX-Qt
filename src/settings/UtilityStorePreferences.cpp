// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/UtilityStorePreferences.h"
#include "util/Utility.h"

void UtilityStorePreferences::setDefaults() {
    QString locNumIntDefault = "1";
    QString loc1LabelDefault = "home";
    QString loc1XDefault = "35.231";
    QString loc1YDefault = "-97.451";
    QString loc1NwsDefault = "OUN";
    QString rid1Default = "TLX";
    Utility::writePref("RADAR_SHOW_COUNTY", "true");
    Utility::writePref("LOC_NUM_INT", locNumIntDefault);
    Utility::writePref("LOC1_X", loc1XDefault);
    Utility::writePref("LOC1_Y", loc1YDefault);
    Utility::writePref("LOC1_NWS", loc1NwsDefault);
    Utility::writePref("LOC1_LABEL", loc1LabelDefault);
    Utility::writePref("NWS1", loc1NwsDefault);
    Utility::writePref("RID1", rid1Default);
    Utility::writePref("CURRENT_LOC_FRAGMENT", "1");
}
