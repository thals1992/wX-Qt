// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTPOLYGONWATCH_H
#define OBJECTPOLYGONWATCH_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "objects/DataStorage.h"
#include "objects/DownloadTimer.h"
#include "objects/LatLon.h"
#include "radar/PolygonType.h"

using std::string;
using std::unordered_map;
using std::vector;

class PolygonWatch {
public:
    explicit PolygonWatch(PolygonType);
    void download();
    string getUrl() const;
    string getPrefTokenStorage() const;
    string prefTokenEnabled() const;
    string getPrefTokenNumberList() const;
    string getPrefTokenLatLon() const;
    string getTypeName() const;
    void update();
    PolygonType type;
    DataStorage storage;
    DataStorage latLonList;
    DataStorage numberList;
    DownloadTimer timer;
    int colorInt;
    bool isEnabled;

    static void load();
    static string getLatLon(const string&);
    static unordered_map<PolygonType, std::unique_ptr<PolygonWatch>> byType;
    static DataStorage watchLatlonCombined;
    static const unordered_map<PolygonType, string> namesByEnumId;
    static const unordered_map<PolygonType, int> colorDefaultByType;
    static const unordered_map<PolygonType, string> colorPrefByType;
    static const vector<PolygonType> polygonList;
};

#endif  // OBJECTPOLYGONWATCH_H
