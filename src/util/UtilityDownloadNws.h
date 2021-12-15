// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYDOWNLOADNWS_H
#define UTILITYDOWNLOADNWS_H

#include <QObject>
#include "objects/LatLon.h"

class UtilityDownloadNws : public QObject  {

    // Q_OBJECT

public:
    static QString getHourlyData(const LatLon&);
    static QString getLocationPointData(const LatLon&);
    static QString get7DayData(const LatLon&);
    static QString getCap(const QString&);
    static QString getHtmlWithXml(const QString&);
};

#endif  // UTILITYDOWNLOADNWS_H
