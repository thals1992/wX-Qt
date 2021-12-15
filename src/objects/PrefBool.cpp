// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/PrefBool.h"
#include "util/To.h"
#include "util/Utility.h"

PrefBool::PrefBool() {
}

PrefBool::PrefBool(const QString& label, const QString& prefToken, bool enabledByDefault) {
    this->label = label;
    this->prefToken = prefToken;
    this->enabledByDefault = enabledByDefault;
}

bool PrefBool::isEnabled() const {
    return Utility::readPref(prefToken, To::String(enabledByDefault)).startsWith("t");
}

bool PrefBool::isEnabled(const QString& s, bool b) {
    return Utility::readPref(s, To::String(b)).startsWith("t");
}
