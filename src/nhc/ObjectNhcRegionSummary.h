// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTNHCREGIONSUMMARY_H
#define OBJECTNHCREGIONSUMMARY_H

#include <QStringList>
#include "nhc/NhcOceanEnum.h"

class ObjectNhcRegionSummary {
public:
    explicit ObjectNhcRegionSummary(const NhcOceanEnum&);
    QStringList urls;
    QStringList titles;
    QString replaceString;
    QString baseUrl;
};

#endif  // OBJECTNHCREGIONSUMMARY_H
