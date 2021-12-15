// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMODELSPCHREFINPUTOUTPUT_H
#define UTILITYMODELSPCHREFINPUTOUTPUT_H

#include "models/ObjectModel.h"
#include "models/RunTimeData.h"

class UtilityModelSpcHrefInputOutput {
public:
    static RunTimeData getRunTime();
    static QStringList getImage(ObjectModel *);
};

#endif  // UTILITYMODELSPCHREFINPUTOUTPUT_H
