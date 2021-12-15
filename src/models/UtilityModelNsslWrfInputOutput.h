// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMODELSNSSLWRFINPUTOUTPUT_H
#define UTILITYMODELSNSSLWRFINPUTOUTPUT_H

#include "models/ObjectModel.h"
#include "models/RunTimeData.h"

class UtilityModelNsslWrfInputOutput {
public:
    static RunTimeData getRunTime(ObjectModel *);
    static QStringList getImage(ObjectModel *);

private:
    static const QString baseUrl;
};

#endif  // UTILITYMODELSNSSLWRFINPUTOUTPUT_H
