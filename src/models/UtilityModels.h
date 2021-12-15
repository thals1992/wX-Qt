// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMODELS_H
#define UTILITYMODELS_H

#include <QStringList>

class UtilityModels {
public:
    static QString convertTimeRuntoTimeString(QString, QString);
    static QStringList updateTime(QString, QString, QStringList, QString);
};

#endif  // UTILITYMODELS_H
