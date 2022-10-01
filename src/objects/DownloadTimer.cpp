// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/DownloadTimer.h"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include "objects/ObjectDateTime.h"
#include "../objects/WString.h"
#include "settings/RadarPreferences.h"

DownloadTimer::DownloadTimer() = default;

DownloadTimer::DownloadTimer(const string& id)
    : identifier{ id }
    , initialized{ false }
    , lastRefresh{ 0.0 }
    , refreshDataInMinutes{ std::max(RadarPreferences::dataRefreshInterval, 6) }
{}

bool DownloadTimer::isRefreshNeeded() {
    refreshDataInMinutes = std::max(RadarPreferences::dataRefreshInterval, 6);
    if (WString::contains(identifier, "WARNINGS")) {
        refreshDataInMinutes = std::max(RadarPreferences::dataRefreshInterval, 3);
    }
    auto refreshNeeded = false;
    const int64_t currentTime = ObjectDateTime::currentTimeMillis();
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

// void DownloadTimer::resetTimer() {
//    lastRefresh = 0.0;
// }
