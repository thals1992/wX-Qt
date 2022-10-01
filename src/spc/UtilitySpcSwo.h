// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCUTILITYSPCSWO_H
#define SPCUTILITYSPCSWO_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class UtilitySpcSwo {
public:
    static string getImageUrlsDays48(const string&);
    static vector<string> getImageUrls(const string&);
};

#endif  // SPCUTILITYSPCSWO_H
