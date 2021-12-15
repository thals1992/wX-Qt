// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYLIGHTNING_H
#define UTILITYLIGHTNING_H

#include <QStringList>

class UtilityLightning {
public:
    static const QStringList sectors;
    static const QStringList times;
    static QString getImageUrl(const QString&, const QString&);
    static QString getSector(const QString&);
    static QString getSectorPretty(const QString&);
    static QString getTime(const QString&);
    static QString getTimePretty(const QString&);
};

#endif  // UTILITYLIGHTNING_H
