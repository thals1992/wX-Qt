// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYUS_H
#define UTILITYUS_H

#include <QStringList>

class UtilityUS {
public:
    static QStringList getCurrentConditionsUS(const QString&, const QString&);
    static QString getLocationHtml(const QString&, const QString&);
    static QString get7DayExt(const QStringList&);
};

#endif  // UTILITYUS_H
