// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef CAPALERT_H
#define CAPALERT_H

#include <QString>

class CapAlert {
public:
    CapAlert();
    explicit CapAlert(const QString&);
    QString url;
    QString html;
    QString title;
    QString summary;
    QString instructions;
    QString area;
    QString text;
    QString vtec;
    QString nwsHeadLine;
    QString windThreat;
    QString maxWindGust;
    QString hailThreat;
    QString maxHailSize;
    QString tornadoThreat;
    QString motion;
};

#endif  // CAPALERT_H
