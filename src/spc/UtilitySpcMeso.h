// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYSPCMESO_H
#define UTILITYSPCMESO_H

#include <string>
#include <vector>
#include "../ui/MenuTitle.h"

using std::string;
using std::vector;

class UtilitySpcMeso {
public:
    static vector<MenuTitle> titles;
    static const vector<string> favList;
    static const vector<string> imgSf;
    static const vector<string> products;
    static const vector<string> labels;
    static const vector<string> sectorCodes;
    static const vector<string> sectors;
};

#endif  // UTILITYSPCMESO_H
