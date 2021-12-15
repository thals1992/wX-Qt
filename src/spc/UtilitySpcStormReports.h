// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCUTILITYSPCSTORMREPORTS_H
#define SPCUTILITYSPCSTORMREPORTS_H

#include <QStringList>
#include <QVector>
#include "spc/StormReport.h"

class UtilitySpcStormReports {
public:
    static QVector<StormReport> process(const QStringList&);
};

#endif  // SPCUTILITYSPCSTORMREPORTS_H
