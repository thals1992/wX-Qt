// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradState.h"
#include <iostream>
#include <memory>
#include "settings/Location.h"
#include "settings/RadarPreferences.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityList.h"

NexradState::NexradState(QWidget * parent,
    int paneNumber, int numberOfPanes, bool useASpecificRadar, const string& radarToUse, int originalWidth, int originalHeight)
    : paneNumber{ paneNumber }
    , numberOfPanes{ numberOfPanes }
    , useASpecificRadar{ useASpecificRadar }
    , radarStatusBox { std::make_unique<RadarStatusBox>(parent) }
    , radarSite{ Location::radarSite() }
    , originalWidth{ originalWidth }
    , originalHeight{ originalHeight }
{
    zoom = 1.0;
    if (numberOfPanes == 2) {
        xPos = 0.0 - (originalWidth / 4.0) * zoom;
    }
    if (!useASpecificRadar) {
        radarProduct = initialRadarProducts[0];
        readPreferences();
    } else {
        setRadar(radarToUse);
        radarProduct = initialRadarProducts[0];
    }
}

ProjectionNumbers NexradState::getPn() const {
    return pn;
}

string NexradState::getRadarSite() const {
    return radarSite;
}

string NexradState::getRadarProduct() const {
    return radarProduct;
}

void NexradState::setRadar(const string& site) {
    radarSite = site;
    pn.setRadarSite(radarSite);
}

void NexradState::reset() {
    xPos = 0.0;
    yPos = 0.0;
    zoom = 1.0;
}

void NexradState::resetZoom() {
    zoom = 1.0;
    xPos = 0.0;
    if (numberOfPanes == 2) {
        xPos = 0.0 - (originalWidth / 4.0) * zoom;
    }
    yPos = 0.0;
}

void NexradState::readPreferences() {
    if (RadarPreferences::rememberLocation) {
        const auto numberOfPanesStr = To::string(numberOfPanes);
        const auto index = To::string(paneNumber);
        zoom = To::Double(Utility::readPref(radarType + numberOfPanesStr + "_ZOOM" + index, "1.0"));
        xPos = To::Double(Utility::readPref(radarType + numberOfPanesStr + "_X" + index, "0.0"));
        yPos = To::Double(Utility::readPref(radarType + numberOfPanesStr + "_Y" + index, "0.0"));
        radarSite = Utility::readPref(radarType + numberOfPanesStr + "_RID" + index, Location::radar());
        radarProduct = Utility::readPref(radarType + numberOfPanesStr + "_PROD" + index, initialRadarProducts[paneNumber]);
        tiltInt = Utility::readPrefInt(radarType + numberOfPanesStr + "_TILT" + index, 0);
        setRadar(radarSite);
    }
}

void NexradState::writePreferences() {
    if (!useASpecificRadar) {
        const auto numberOfPanesStr = To::string(numberOfPanes);
        const auto index = To::string(paneNumber);
        Utility::writePref(radarType + numberOfPanesStr + "_ZOOM" + index, To::string(zoom));
        Utility::writePref(radarType + numberOfPanesStr + "_X" + index, To::string(xPos));
        Utility::writePref(radarType + numberOfPanesStr + "_Y" + index, To::string(yPos));
        Utility::writePref(radarType + numberOfPanesStr + "_RID" + index, radarSite);
        Utility::writePref(radarType + numberOfPanesStr + "_PROD" + index, radarProduct);
        Utility::writePrefInt(radarType + numberOfPanesStr + "_TILT" + index, tiltInt);
    }
}

void NexradState::processAnimationFiles(int frameCount, FileStorage * fileStorage) {
    for (auto index : range(frameCount)) {
        levelDataList.emplace_back(this, fileStorage);
        levelDataList.back().radarBuffers.animationIndex = index;
        levelDataList.back().decode();
        levelDataList.back().radarBuffers.initialize();
        levelDataList.back().generateRadials();
    }
}
