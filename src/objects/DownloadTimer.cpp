// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/DownloadTimer.h"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include "settings/RadarPreferences.h"
#include "util/UtilityTime.h"

DownloadTimer::DownloadTimer() {
}

DownloadTimer::DownloadTimer(const QString& id) {
    identifier = id;
    initialized = false;
    lastRefresh = 0.0;
    refreshDataInMinutes = std::max(RadarPreferences::dataRefreshInterval, 6);
}

bool DownloadTimer::isRefreshNeeded() {
    refreshDataInMinutes = std::max(RadarPreferences::dataRefreshInterval, 6);
    if (identifier.contains("WARNINGS")) {
        refreshDataInMinutes = std::max(RadarPreferences::dataRefreshInterval, 3);
    }
    auto refreshNeeded = false;
    const int64_t currentTime = UtilityTime::currentTimeMillis();
    const int64_t currentTimeSeconds = currentTime / 1000;
    const int64_t refreshIntervalSeconds = refreshDataInMinutes * 60;
    if (currentTimeSeconds > (lastRefresh + refreshIntervalSeconds) || !initialized) {
        refreshNeeded = true;
        initialized = true;
        lastRefresh = currentTime / 1000;
    }
    // print("REFRESH CHECK FOR ", self.identifier, refreshNeeded);
    return refreshNeeded;
}

void DownloadTimer::resetTimer() {
    lastRefresh = 0.0;
}
