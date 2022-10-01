// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef PREFBOOL_H
#define PREFBOOL_H

#include <string>

using std::string;

class PrefBool {
public:
    PrefBool(const string& label, const string& prefToken, bool enabledByDefault);
    bool isEnabled() const;
    string label;
    string prefToken;
    bool enabledByDefault;
};

#endif  // PREFBOOL_H
