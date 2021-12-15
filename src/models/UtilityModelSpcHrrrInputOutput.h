// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMODELSPCHRRRRINPUTOUTPUT_H
#define UTILITYMODELSPCHRRRRINPUTOUTPUT_H

#include "models/ObjectModel.h"

class UtilityModelSpcHrrrInputOutput {
public:
    static RunTimeData getRunTime();
    static QString getImage(ObjectModel *);
    static QString getSectorCode(const QString&);
    static QString getValidTime(const QString&, const QString&, const QString&);
    static QString formatTime(const QString&);
};

#endif  // UTILITYMODELSPCHRRRRINPUTOUTPUT_H
