// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMODELSPCSREFINPUTOUTPUT_H
#define UTILITYMODELSPCSREFINPUTOUTPUT_H

#include "models/ObjectModel.h"

class UtilityModelSpcSrefInputOutput {
public:
    static QString pattern1;
    static QString pattern2;
    static RunTimeData getRunTime();
    static QString getImage(ObjectModel *);
};

#endif  // UTILITYMODELSPCSREFINPUTOUTPUT_H
