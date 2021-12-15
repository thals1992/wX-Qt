// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradState.h"
#include "settings/Location.h"
#include "util/To.h"
#include "util/Utility.h"

NexradState::NexradState() {}

NexradState::NexradState(int paneNumber, int numberOfPanes, bool useASpecificRadar) {
    this->paneNumber = paneNumber;
    this->numberOfPanes = numberOfPanes;
    this->useASpecificRadar = useASpecificRadar;
}

void NexradState::reset() {
    xPos = 0.0;
    yPos = 0.0;
    zoom = 1.0;
}

void NexradState::readPreferences() {
    auto numberOfPanesStr = To::String(numberOfPanes);
    QString radarType = "WXMETAL";
    auto index = To::String(paneNumber);
    zoom = To::Double(Utility::readPref(radarType + numberOfPanesStr + "_ZOOM" + index, "1.0"));
    xPos = To::Double(Utility::readPref(radarType + numberOfPanesStr + "_X" + index, "0.0"));
    yPos = To::Double(Utility::readPref(radarType + numberOfPanesStr + "_Y" + index, "0.0"));
    radarSite = Utility::readPref(radarType + numberOfPanesStr + "_RID" + index, Location::radar());
    radarProduct = Utility::readPref(radarType + numberOfPanesStr + "_PROD" + index, initialRadarProducts[paneNumber]);
    tiltInt = Utility::readPrefInt(radarType + numberOfPanesStr + "_TILT" + index, 0);
}

void NexradState::writePreferences() {
    if (!useASpecificRadar) {
        QString radarType = "WXMETAL";
        auto numberOfPanesStr = To::String(numberOfPanes);
        auto index = To::String(paneNumber);
        Utility::writePref(radarType + numberOfPanesStr + "_ZOOM" + index, To::String(zoom));
        Utility::writePref(radarType + numberOfPanesStr + "_X" + index, To::String(xPos));
        Utility::writePref(radarType + numberOfPanesStr + "_Y" + index, To::String(yPos));
        Utility::writePref(radarType + numberOfPanesStr + "_RID" + index, radarSite);
        Utility::writePref(radarType + numberOfPanesStr + "_PROD" + index, radarProduct);
        Utility::writePrefInt(radarType + numberOfPanesStr + "_TILT" + index, tiltInt);
    }
}
