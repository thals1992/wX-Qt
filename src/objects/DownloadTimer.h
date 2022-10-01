// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef DOWNLOADTIMER_H
#define DOWNLOADTIMER_H

#include <string>

using std::string;

class DownloadTimer {
public:
    DownloadTimer();
    explicit DownloadTimer(const string&);
    bool isRefreshNeeded();

private:
    string identifier;
    bool initialized{};
    float lastRefresh{};
    int refreshDataInMinutes{};
};

#endif  // DOWNLOADTIMER_H
