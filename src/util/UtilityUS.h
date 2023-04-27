// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYUS_H
#define UTILITYUS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class UtilityUS {
public:
    static vector<string> getCurrentConditionsUS(const string&, const string&);
    static string getLocationHtml(const string&, const string&);
    static string get7DayExt(const vector<string>&);

private:
    static const vector<string> regexpList;
};

#endif  // UTILITYUS_H
