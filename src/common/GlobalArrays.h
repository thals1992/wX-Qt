// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef GLOBALARRAYS_H
#define GLOBALARRAYS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class GlobalArrays {
public:
    static string getRadarCodeAtIndex(int);
    static vector<string> radars();
    static vector<string> tdwrRadarCodes();
    static vector<string> nexradRadarCodes();
    static const vector<string> wfos;
    static const vector<string> nexradRadars;
    static const vector<string> tdwrRadars;
};

#endif  // GLOBALARRAYS_H
