// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYMETAR_H
#define UTILITYMETAR_H

#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include "objects/FileStorage.h"
#include "objects/LatLon.h"
#include "radar/RID.h"

using std::string;
using std::unordered_map;
using std::vector;

class UtilityMetar {
public:
    static RID findClosestObservation(const LatLon&, int index = 0);
    static void getStateMetarArrayForWXOGL(const string&, FileStorage&);
    static string getObservationSites(const string&);
    static vector<string> condenseObs(const vector<string>&);

private:
    static void readMetarData();
    static const string metarFileName;
    static bool initializedObsMap;
    static unordered_map<string, LatLon> obsLatlon;
    static vector<string> metarDataRaw;
    static vector<RID> metarSites;
    static std::mutex mtx;
};

#endif  // UTILITYMETAR_H
