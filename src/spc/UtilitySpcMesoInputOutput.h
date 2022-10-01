// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYSPCMESOINPUTOUTPUT_H
#define UTILITYSPCMESOINPUTOUTPUT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class UtilitySpcMesoInputOutput {
public:
    static vector<string> getAnimation(const string&, const string&, size_t);
};

#endif  // UTILITYSPCMESOINPUTOUTPUT_H
