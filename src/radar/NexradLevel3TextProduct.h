// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NEXRADLEVEL3TEXTPRODUCT_H
#define NEXRADLEVEL3TEXTPRODUCT_H

#include "../objects/FileStorage.h"
#include "ProjectionNumbers.h"

class NexradLevel3TextProduct {
public:
    static string download(const string& product, const string& radarSite);
};

#endif  // NEXRADLEVEL3TEXTPRODUCT_H
