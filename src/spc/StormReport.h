// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef STORMREPORT_H
#define STORMREPORT_H

#include <QString>

class StormReport {
public:
    StormReport();
    StormReport(const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&, const QString&);
    QString text;
    QString lat;
    QString lon;
    QString time;
    QString magnitude;
    QString address;
    QString city;
    QString state;
    QString damageReport;
    QString damageHeader;
};

#endif  // STORMREPORT_H
