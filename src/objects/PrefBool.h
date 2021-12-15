// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef PREFBOOL_H
#define PREFBOOL_H

#include <QString>

class PrefBool {
public:
    PrefBool();
    PrefBool(const QString& label, const QString& prefToken, bool enabledByDefault);
    bool isEnabled() const;
    static bool isEnabled(const QString& s, bool b);
    QString label;
    QString prefToken;
    bool enabledByDefault;
};

#endif  // PREFBOOL_H
