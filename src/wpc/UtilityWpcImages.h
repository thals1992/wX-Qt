// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYWPCIMAGES_H
#define UTILITYWPCIMAGES_H

#include <string>
#include <vector>
#include "../ui/ObjectMenuTitle.h"

using std::string;
using std::vector;

class UtilityWpcImages {
public:
    static vector<ObjectMenuTitle> titles;
    static const vector<string> urls;
    static const vector<string> labels;
};

#endif  // UTILITYWPCIMAGES_H
