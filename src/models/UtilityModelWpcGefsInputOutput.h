// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMODELWPCGEFSINPUTOUTPUT_H
#define UTILITYMODELWPCGEFSINPUTOUTPUT_H

#include "models/ObjectModel.h"

class UtilityModelWpcGefsInputOutput {
public:
    static RunTimeData getRunTime();
    static QString getImage(ObjectModel *);
};

#endif  // UTILITYMODELWPCGEFSINPUTOUTPUT_H
