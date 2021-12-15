// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef GLOBALARRAYS_H
#define GLOBALARRAYS_H

#include <QStringList>

class GlobalArrays {
public:
    static QString getRadarCodeAtIndex(int);
    static QStringList radars();
    static QStringList tdwrRadarCodes();
    static QStringList nexradRadarCodes();
    static const QStringList states;
    static const QStringList wfos;
    static const QStringList nexradRadars;
    static const QStringList soundingSites;
    static const QStringList nwsImageProducts;
    static const QStringList tdwrRadars;
    static const QStringList tdwrRadarsForMap;
};

#endif  // GLOBALARRAYS_H
