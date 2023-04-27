// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYSWODAYONE_H
#define UTILITYSWODAYONE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <QColor>
#include "objects/DownloadTimer.h"

using std::string;
using std::unordered_map;
using std::vector;

class SwoDayOne {
public:
    static void get();
    static DownloadTimer timer;
    static unordered_map<int, vector<double>> hashSwo;
    static const vector<QColor> swoPaints;
    static const vector<string> threatList;
};

#endif  // UTILITYSWODAYONE_H
