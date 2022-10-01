// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMODELSPCHREFINPUTOUTPUT_H
#define UTILITYMODELSPCHREFINPUTOUTPUT_H

#include <string>
#include "ObjectModel.h"
#include "RunTimeData.h"

class UtilityModelSpcHrefInputOutput {
public:
    static RunTimeData getRunTime();
    static string getImageUrl(ObjectModel *);
};

#endif  // UTILITYMODELSPCHREFINPUTOUTPUT_H
