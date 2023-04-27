// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLNEXRADLEVEL3TVS_H
#define WXGLNEXRADLEVEL3TVS_H

#include <vector>
#include "objects/FileStorage.h"
#include "radar/ProjectionNumbers.h"

using std::vector;

class NexradLevel3Tvs {
public:
    static void decode(const ProjectionNumbers&, FileStorage&);
};

#endif  // WXGLNEXRADLEVEL3TVS_H
