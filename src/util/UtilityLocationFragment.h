// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYLOCATIONFRAGMENT_H
#define UTILITYLOCATIONFRAGMENT_H

#include <QHash>
#include <QStringList>

class UtilityLocationFragment {
public:
    static QString extract7DayMetrics(const QString&);
    static QString extractWindDirection(const QString&);
    static QString extractTemp(const QString&);

private:
    static const QString nws7dayTemp1;
    static const QString nws7dayTemp2;
    static const QString nws7dayTemp3;
    static const QString nws7dayTemp4;
    static const QString nws7dayTemp5;
    static const QString nws7dayTemp6;
    static const QString nws7dayTemp7;
    static const QString nws7dayTemp8;
    static const QString nws7dayTemp9;
    static const QString nws7dayTemp10;
    static const QString nws7dayTemp11;
    static const QString sevenDayWind1;
    static const QString sevenDayWind2;
    static const QString sevenDayWind3;
    static const QString sevenDayWind4;
    static const QString sevenDayWind5;
    static const QString sevenDayWind6;
    static const QString sevenDayWind7;
    static const QString sevenDayWind8;
    static const QString sevenDayWind9;
    static const QHash<QString, QString> windDir;
};

#endif  // UTILITYLOCATIONFRAGMENT_H
