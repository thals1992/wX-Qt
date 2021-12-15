// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXMETALNEXRADLEVELDATA_H
#define WXMETALNEXRADLEVELDATA_H

#include <cstdint>
#include <memory>
#include <QString>
#include "objects/MemoryBuffer.h"
#include "radar/ObjectMetalRadarBuffers.h"

class WXMetalNexradLevelData {
public:
    WXMetalNexradLevelData();
    WXMetalNexradLevelData(const QString&, ObjectMetalRadarBuffers *, const QString&);
    void decode();
    MemoryBuffer radialStartAngle;
    double binSize;
    int numberOfRangeBins;
    int numberOfRadials;
    MemoryBuffer binWord;
    int16_t productCode;
    ObjectMetalRadarBuffers * radarBuffers;
    QString index;
    int radarHeight;
    double degree;
    int16_t operationalMode;
    int16_t volumeCoveragePattern;
    int16_t elevationAngle;
    int generateRadials();

private:
    void decodeAndPlotNexradLevel3();
    void decodeAndPlotNexradLevel3FourBit();
    void writeTime(int16_t, int) const;
    int decodeRadial4bit();
    int decodeRaster();
    double latitudeOfRadar;
    double longitudeOfRadar;
    uint16_t sequenceNumber;
    uint16_t volumeScanNumber;
    uint16_t elevationNumber;
    float halfWord3132;
    QString timestampStr;
    int64_t seekStart;
    int compressedFileSize;
    uint16_t volumeScanDate;
    int volumeScanTime;
};

#endif  // WXMETALNEXRADLEVELDATA_H
