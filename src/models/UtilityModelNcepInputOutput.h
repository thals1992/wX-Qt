// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMODELSNCEPINPUTOUTPUT_H
#define UTILITYMODELSNCEPINPUTOUTPUT_H

#include "models/ObjectModel.h"

class UtilityModelNcepInputOutput {
public:
    static RunTimeData getRunTime(ObjectModel *);
    static QString getImage(ObjectModel *);

private:
    static const QString pattern;
};

#endif  // UTILITYMODELSNCEPINPUTOUTPUT_H
