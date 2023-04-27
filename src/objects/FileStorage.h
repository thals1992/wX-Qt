// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include <QByteArray>
#include <QLineF>
#include <QVector>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "objects/DownloadTimer.h"
#include "objects/MemoryBuffer.h"
#include "radar/RadarGeometryTypeEnum.h"

using std::string;
using std::unordered_map;
using std::vector;

class FileStorage {
public:
    FileStorage();
    void clearBuffers();
    void setMemoryBuffer(const QByteArray&);
    void setMemoryBufferForAnimation(int, const QByteArray&);
    MemoryBuffer memoryBuffer;
    vector<MemoryBuffer> animationMemoryBuffer;
    string radarInfo;
    int radarAgeMilli{};
    vector<double> stiData;
    vector<double> hiData;
    vector<double> tvsData;
    vector<string> obsArr;
    vector<string> obsArrExt;
    vector<string> obsArrWb;
    vector<string> obsArrWbGust;
    vector<double> obsArrX;
    vector<double> obsArrY;
    vector<int> obsArrAviationColor;
    string obsOldRadarSite;
    DownloadTimer obsDownloadTimer;
    unordered_map<RadarGeometryTypeEnum, QVector<QLineF>> relativeBuffers;
    vector<double> locationDotsTransformed;
    vector<double> locationDotsTransformedGps;
    // double gpsX{};
    // double gpsY{};
};

#endif  // FILESTORAGE_H
