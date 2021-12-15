// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLNEXRADLEVEL3WINDBARBS_H
#define WXGLNEXRADLEVEL3WINDBARBS_H

#include <QVector>
#include "objects/FileStorage.h"
#include "util/ProjectionNumbers.h"

class WXGLNexradLevel3WindBarbs {
public:
    static QVector<float> decodeAndPlot(const ProjectionNumbers&, bool, FileStorage&);
};

#endif  // WXGLNEXRADLEVEL3WINDBARBS_H
