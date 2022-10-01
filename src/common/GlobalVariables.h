// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include <string>

using std::string;

class GlobalVariables {
public:
    static const string aboutString;
    static const string mainScreenShortcuts;
    static const string nexradShortcuts;
    static const string appCreatorEmail;
    static const string appName;
    static const string resDir;
    static const string imageDir;
    static const string newline;
    static const string degreeSymbol;
    static const string nwsSPCwebsitePrefix;
    static const string nwsWPCwebsitePrefix;
    static const string nwsAWCwebsitePrefix;
    static const string nwsGraphicalWebsitePrefix;
    static const string nwsNhcWebsitePrefix;
    static const string goes16Url;
    static const string nwsApiUrl;
    static const string tgftpSitePrefix;
    static const string prePattern;
    static const string pre2Pattern;
    static const string vtecPattern;
    static const string warningLatLonPattern;
    static const string utilUsPeriodNamePattern;
    static const string xmlValuePattern;
};

#endif  // GLOBALVARIABLES_H
