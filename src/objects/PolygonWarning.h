// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTPOLYGONWARNING_H
#define OBJECTPOLYGONWARNING_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "objects/DataStorage.h"
#include "objects/DownloadTimer.h"
#include "radar/PolygonType.h"

using std::string;
using std::unordered_map;
using std::vector;

class PolygonWarning {
public:
    explicit PolygonWarning(const PolygonType&);
    void download();
    string getData() const;
    string typeName() const;
    string getTypeName() const;
    string prefTokenEnabled() const;
    string prefTokenStorage() const;
    string prefTokenColor() const;
    int color() const;
    string name() const;
    string urlToken() const;
    string url() const;
    string getUrl() const;
    int getCount() const;
    void update();
    PolygonType type;
    bool isEnabled;
    DataStorage storage;
    DownloadTimer timer;
    int colorInt;

    static const string pVtec;
    static const string baseUrl;
    static const unordered_map<PolygonType, int> defaultColors;
    static const unordered_map<PolygonType, string> longName;
    static const vector<PolygonType> polygonList;
    static const unordered_map<PolygonType, string> namesByEnumId;
    static unordered_map<PolygonType, std::unique_ptr<PolygonWarning>> byType;
    static string getLongName(PolygonType);
    static string getShortName(PolygonType);
    static bool areAnyEnabled();
    static bool isCountNonZero();
    static void load();
};

#endif  // OBJECTPOLYGONWARNING_H
