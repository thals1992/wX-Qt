// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTMODELGET_H
#define OBJECTMODELGET_H

#include "models/ObjectModel.h"

class ObjectModelGet {
public:
    static void getRunStatus(ObjectModel&);
    static QString getImageUrl(ObjectModel&);
};

#endif  // OBJECTMODELGET_H
