// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RUNTIMEDATA_H
#define RUNTIMEDATA_H

#include <QStringList>

class RunTimeData {
public:
    RunTimeData();
    void appendListRun(const QString&);
    void appendListRun(const QStringList&);
    QStringList listRun;
    QString mostRecentRun;
    int imageCompleteInt;
    QString imageCompleteStr;
    QString timeStringConversion;
    QString validTime;
};

#endif  // RUNTIMEDATA_H
