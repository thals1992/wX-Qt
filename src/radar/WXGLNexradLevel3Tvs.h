// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLNEXRADLEVEL3TVS_H
#define WXGLNEXRADLEVEL3TVS_H

#include <QVector>
#include "objects/FileStorage.h"
#include "util/ProjectionNumbers.h"

class WXGLNexradLevel3Tvs {
public:
    static void decode(const ProjectionNumbers&, FileStorage&);
};

#endif  // WXGLNEXRADLEVEL3TVS_H
