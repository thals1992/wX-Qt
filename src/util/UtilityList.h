// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYLIST_H
#define UTILITYLIST_H

#include <QStringList>
#include <QVector>

class UtilityList {
public:
    static int findex(const QString&, const QStringList&);
    static int indexOf(const QStringList&, const QString&);
    static QVector<int> range(int);
    static QVector<int> range2(int, int);
    static QVector<int> range3(int, int, int);
    static QStringList reversed(const QStringList&);
};

#endif  // UTILITYLIST_H
