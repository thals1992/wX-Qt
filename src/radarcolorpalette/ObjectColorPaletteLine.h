// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCOLORPALETTELINE_H
#define OBJECTCOLORPALETTELINE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class ObjectColorPaletteLine {
public:
    explicit ObjectColorPaletteLine(const vector<string>&);
    ObjectColorPaletteLine(int, const string&, const string&, const string&);
    vector<double> asVector() const;
    int dbz{};
    int red{};
    int green{};
    int blue{};
};

#endif  // OBJECTCOLORPALETTELINE_H
