// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLNEXRADLEVEL3HAILINDEX_H
#define WXGLNEXRADLEVEL3HAILINDEX_H

#include <QVector>
#include "objects/FileStorage.h"
#include "util/ProjectionNumbers.h"

class WXGLNexradLevel3HailIndex {
public:
    static void decode(const ProjectionNumbers&, FileStorage&);

private:
    static const QString pattern;
};

#endif  // WXGLNEXRADLEVEL3HAILINDEX_H
