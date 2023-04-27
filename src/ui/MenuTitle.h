// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTMENUTITLE_H
#define OBJECTMENUTITLE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class MenuTitle {
public:
    MenuTitle(const string&, int);
    void setList(const vector<string>&, int);
    vector<string> get() const;
    vector<string> items;
    string title;
    int count;
};

#endif  // OBJECTMENUTITLE_H
