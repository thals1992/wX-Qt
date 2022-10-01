// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYDOWNLOADNWS_H
#define UTILITYDOWNLOADNWS_H

#include <QObject>
#include "objects/LatLon.h"

class UtilityDownloadNws : public QObject  {

public:
    static string getHourlyData(const LatLon&);
    static string getLocationPointData(const LatLon&);
    static string get7DayData(const LatLon&);
    static string getCap(const string&);
    static string getHtmlWithXml(const string&);
};

#endif  // UTILITYDOWNLOADNWS_H
