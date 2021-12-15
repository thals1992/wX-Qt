// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYHOURLYOLDAPI_H
#define UTILITYHOURLYOLDAPI_H

#include <QHash>
#include <QStringList>

using namespace std;

class UtilityHourlyOldApi {
public:
    static QString getHourlyString(int);

private:
    static QString parseHourly(const QString&);
};

#endif  // UTILITYHOURLYOLDAPI_H
