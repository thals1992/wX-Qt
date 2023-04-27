// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLNEXRADLEVEL3HAILINDEX_H
#define WXGLNEXRADLEVEL3HAILINDEX_H

#include <string>
#include <vector>
#include "objects/FileStorage.h"
#include "radar/ProjectionNumbers.h"

using std::string;
using std::vector;

class NexradLevel3HailIndex {
public:
    static void decode(const ProjectionNumbers&, FileStorage&);

private:
    static const string pattern;
};

#endif  // WXGLNEXRADLEVEL3HAILINDEX_H
