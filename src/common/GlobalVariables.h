// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <QString>

class GlobalVariables {
public:
    static const QString aboutString;
    static const QString mainScreenShortcuts;
    static const QString nexradShortcuts;
    static const QString appCreatorEmail;
    static const QString appName;
    static const QString resDir;
    static const QString imageDir;
    static const QString newline;
    static const QString degreeSymbol;
    static const QString nwsSPCwebsitePrefix;
    static const QString nwsWPCwebsitePrefix;
    static const QString nwsAWCwebsitePrefix;
    static const QString nwsGraphicalWebsitePrefix;
    static const QString nwsCPCNcepWebsitePrefix;
    static const QString nwsGoesWebsitePrefix;
    static const QString nwsOpcWebsitePrefix;
    static const QString nwsNhcWebsitePrefix;
    static const QString nwsRadarWebsitePrefix;
    static const QString nwsMagNcepWebsitePrefix;
    static const QString nwsSwpcWebSitePrefix;
    static const QString goes16Url;
    static const QString nwsApiUrl;
    static const QString tgftpSitePrefix;
    static const QString prePattern;
    static const QString pre2Pattern;
    static const QString vtecPattern;
    static const QString warningLatLonPattern;
    static const QString utilUsPeriodNamePattern;
    static const QString xmlValuePattern;
};

#endif  // GLOBALVARIABLES_H
