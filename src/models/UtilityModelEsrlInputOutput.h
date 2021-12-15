// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMODELSESRLINPUTOUTPUT_H
#define UTILITYMODELSESRLINPUTOUTPUT_H

#include "models/ObjectModel.h"
#include "models/RunTimeData.h"

class UtilityModelEsrlInputOutput {
public:
    static RunTimeData getRunTime(ObjectModel *);
    static QString getImage(ObjectModel *);

private:
    static const QString pattern1;
    static const QString pattern2;
    static const QString pattern3;
    static const QString pattern4;
    static const QString pattern5;
    static const QString pattern6;
};

#endif  // UTILITYMODELSESRLINPUTOUTPUT_H
