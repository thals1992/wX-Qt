// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYDOWNLOAD_H
#define UTILITYDOWNLOAD_H

#include <string>

using std::string;

class DownloadText {
public:
    static string byProduct(const string&);
    static string getTextProductWithVersion(const string&, int);
    static string getRadarStatusMessage(const string&);

private:
    static bool useNwsApi;
};

#endif  // UTILITYDOWNLOAD_H
