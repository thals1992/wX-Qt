// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYHOURLY_H
#define UTILITYHOURLY_H

#include <QHash>
#include <QStringList>

class UtilityHourly {
public:
    static QString get(int);

private:
    static QHash<QString, QString> hourlyAbbreviations;
    static QString getFooter();
    static QString getHourlyString(int);
    static QString parse(const QString&);
    static QString shortenConditions(const QString&);
    static QString translateTime(const QString&);
};

#endif  // UTILITYHOURLY_H
