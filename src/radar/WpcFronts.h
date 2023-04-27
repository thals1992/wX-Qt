// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYWPCFRONTS_H
#define UTILITYWPCFRONTS_H

#include <string>
#include <vector>
#include "objects/DownloadTimer.h"
#include "radar/Fronts.h"
#include "radar/PressureCenter.h"

using std::string;
using std::vector;

class WpcFronts {
public:
    static const string separator;
    static vector<PressureCenter> pressureCenters;
    static vector<Fronts> fronts;
    static DownloadTimer timer;
    static void get();

private:
    static void addColdFrontTriangles(Fronts *, const vector<string>&);
    static void addWarmFrontSemicircles(Fronts *, const vector<string>&);
    static void addFrontDataStationaryWarm(Fronts *, const vector<string>&);
    static void addFrontDataTrof(Fronts *, const vector<string>&);
    static void addFrontData(Fronts *, const vector<string>&);
    static vector<double> parseLatLon(const string&);
};

#endif  // UTILITYWPCFRONTS_H
