// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef DOWNLOADTIMER_H
#define DOWNLOADTIMER_H

#include <QString>

class DownloadTimer {
public:
    DownloadTimer();
    explicit DownloadTimer(const QString&);
    bool isRefreshNeeded();
    void resetTimer();

private:
    QString identifier;
    bool initialized;
    float lastRefresh;
    int refreshDataInMinutes;
};

#endif  // DOWNLOADTIMER_H
