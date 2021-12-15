// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCUTILITYSPCSWO_H
#define SPCUTILITYSPCSWO_H

#include <QStringList>

class UtilitySpcSwo {
public:
    static QString getImageUrlsDays48(const QString&);
    static QStringList getImageUrls(const QString&);
};

#endif  // SPCUTILITYSPCSWO_H
