// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXMETALNEXRADLEVELDATA_H
#define WXMETALNEXRADLEVELDATA_H

#include <cstdint>
#include <memory>
#include "objects/FileStorage.h"
#include "objects/MemoryBuffer.h"
#include "radar/RadarBuffers.h"

class NexradState;

class NexradLevelData {
public:
    NexradLevelData(NexradState *, FileStorage *);
    void decode();
    void generateRadials();
    FileStorage * fileStorage{};
    double binSize{};
    int numberOfRangeBins{};
    int numberOfRadials{};
    uint16_t productCode{};
    RadarBuffers radarBuffers;
    int radarHeight{};
    double degree{};
    uint16_t operationalMode{};
    uint16_t volumeCoveragePattern{};
    int16_t elevationAngle{};
    int totalBins{};
    string radarInfo;
    int radarAgeMilli{};

private:
    void decodeAndPlotNexradLevel3();
    void decodeAndPlotNexradLevel3FourBit();
    void writeTime(uint16_t, int);
    double latitudeOfRadar{};
    double longitudeOfRadar{};
    uint16_t sequenceNumber{};
    uint16_t volumeScanNumber{};
    uint16_t elevationNumber{};
    float halfWord3132{};
    int64_t seekStart{};
    uint16_t volumeScanDate{};
    int volumeScanTime{};
    NexradState * nexradState{};
};

#endif  // WXMETALNEXRADLEVELDATA_H
