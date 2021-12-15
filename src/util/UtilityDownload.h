// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYDOWNLOAD_H
#define UTILITYDOWNLOAD_H

#include <QString>

class UtilityDownload {

public:
    static QString getTextProduct(const QString&);
    static QString getImageProduct(const QString&);
    static QString getTextProductWithVersion(const QString&, int);
    static QString getRadarStatusMessage(const QString&);
};

#endif  // UTILITYDOWNLOAD_H
