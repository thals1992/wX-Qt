// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradLevelData.h"
#include <iostream>
#include <vector>
#include "common/GlobalDictionaries.h"
#include "objects/ObjectDateTime.h"
#include "radar/NexradState.h"
#include "radar/NexradDecodeEightBit.h"
#include "radar/NexradDecodeFourBit.h"
#include "radar/NexradRaster.h"
#include "radar/NexradUtil.h"
#include "util/To.h"
#include "util/UtilityList.h"

NexradLevelData::NexradLevelData(NexradState * nexradState, FileStorage * fileStorge)
    : fileStorage{ fileStorge }
    , numberOfRangeBins{ 916 }
    , numberOfRadials{ 360 }
    , productCode{ static_cast<uint16_t>(GlobalDictionaries::radarProductStringToShortInt.at(nexradState->getRadarProduct())) }
    , nexradState{ nexradState }
{}

void NexradLevelData::decode() {
    productCode = GlobalDictionaries::radarProductStringToShortInt.at(nexradState->getRadarProduct());
    switch (productCode) {
        case 155:
        case 30:
        case 37:
        case 38:
        case 41:
        case 56:
        case 57:
        case 78:
        case 80:
        case 181:
            decodeAndPlotNexradLevel3FourBit();
            break;
        default:
            decodeAndPlotNexradLevel3();
            break;
    }
}

void NexradLevelData::generateRadials() {
    if (contains({37, 38}, productCode)) {
        totalBins = NexradRaster::create(&radarBuffers, this);
    } else if (contains({30, 56, 78, 80, 181}, productCode)) {
        totalBins = NexradDecodeEightBit::createRadials(&radarBuffers);
    } else {
        totalBins = NexradDecodeEightBit::andCreateRadials(&radarBuffers, fileStorage);
    }
}

void NexradLevelData::decodeAndPlotNexradLevel3() {
    MemoryBuffer * dis;
    if (radarBuffers.animationIndex == -1) {
        dis = &(fileStorage->memoryBuffer);
    } else {
        dis = &(fileStorage->animationMemoryBuffer[radarBuffers.animationIndex]);
    }
    dis->setPosition(0);
    if (dis->getCapacity() > 0) {
        while (dis->getShort() != -1) {}
        latitudeOfRadar = (dis->getInt()) / 1000.0;
        longitudeOfRadar = (dis->getInt()) / 1000.0;
        radarHeight = dis->getUnsignedShort();
        productCode = dis->getUnsignedShort();
        operationalMode = dis->getUnsignedShort();
        volumeCoveragePattern = dis->getUnsignedShort();
        sequenceNumber = dis->getUnsignedShort();
        volumeScanNumber = dis->getUnsignedShort();
        volumeScanDate = dis->getUnsignedShort();
        volumeScanTime = dis->getInt();
        writeTime(volumeScanDate, volumeScanTime);
        dis->skipBytes(10);
        elevationNumber = dis->getUnsignedShort();
        elevationAngle = dis->getShort();
        degree = elevationAngle / 10.0;
        halfWord3132 = dis->getFloat();
        NexradUtil::wxoglDspLegendMax = (255.0 / halfWord3132) * 0.01;
        dis->skipBytes(26);
        dis->skipBytes(30);
        seekStart = dis->getPosition();
        binSize = NexradUtil::getBinSize(productCode);
        numberOfRangeBins = NexradUtil::getNumberRangeBins(productCode);
        numberOfRadials = 360;
        if (productCode == 153 || productCode == 154) {
            numberOfRadials = 720;
        }
        radarBuffers.numberOfRangeBins = numberOfRangeBins;
        radarBuffers.numberOfRadials = numberOfRadials;
        radarBuffers.binSize = binSize;
        radarBuffers.productCode = productCode;
    }
}

void NexradLevelData::decodeAndPlotNexradLevel3FourBit() {
    switch (productCode) {
        case 181:
            radarBuffers.binWord = MemoryBuffer{360 * 720};
            break;
        case 78:
            radarBuffers.binWord = MemoryBuffer{360 * 592};
            break;
        case 80:
            radarBuffers.binWord = MemoryBuffer{360 * 592};
            break;
        case 37:
            radarBuffers.binWord = MemoryBuffer{464 * 464};
            break;
        case 38:
            radarBuffers.binWord = MemoryBuffer{464 * 464};
            break;
        default:
            radarBuffers.binWord = MemoryBuffer{360 * 230};
            break;
    }
    radarBuffers.radialStartAngle = MemoryBuffer{4 * 360};
    MemoryBuffer * dis;
    if (radarBuffers.animationIndex == -1) {
        dis = &(fileStorage->memoryBuffer);
    } else {
        dis = &(fileStorage->animationMemoryBuffer[radarBuffers.animationIndex]);
        dis->setPosition(0);
    }
    if (dis->getCapacity() > 0) {
        dis->skipBytes(30);
        dis->skipBytes(20);
        dis->skipBytes(8);
        [[maybe_unused]] int radarHeight = dis->getUnsignedShort();
        auto productCode = dis->getUnsignedShort();
        [[maybe_unused]] uint16_t operationalMode = dis->getUnsignedShort();
        volumeCoveragePattern = dis->getUnsignedShort();
        sequenceNumber = dis->getUnsignedShort();
        volumeScanNumber = dis->getUnsignedShort();
        auto volumeScanDate = dis->getUnsignedShort();
        auto volumeScanTime = dis->getInt();
        writeTime(volumeScanDate, volumeScanTime);
        dis->skipBytes(6);
        dis->skipBytes(56);
        dis->skipBytes(32);
        switch (productCode) {
        case 37:
            numberOfRangeBins = NexradDecodeFourBit::raster(&radarBuffers, fileStorage);
            break;
        case 38:
            numberOfRangeBins = NexradDecodeFourBit::raster(&radarBuffers, fileStorage);
            break;
        case 41:
            numberOfRangeBins = NexradDecodeFourBit::raster(&radarBuffers, fileStorage);
            break;
        case 57:
            numberOfRangeBins = NexradDecodeFourBit::raster(&radarBuffers, fileStorage);
            break;
        default:
            numberOfRangeBins = NexradDecodeFourBit::radial(&radarBuffers, fileStorage);
            break;
        }
        binSize = NexradUtil::getBinSize(productCode);
        numberOfRadials = 360;
    } else {
        numberOfRangeBins = 230;
        numberOfRadials = 360;
    }
    radarBuffers.numberOfRangeBins = numberOfRangeBins;
    radarBuffers.numberOfRadials = numberOfRadials;
    radarBuffers.binSize = binSize;
    radarBuffers.productCode = productCode;
}

void NexradLevelData::writeTime(uint16_t volumeScanDate, int volumeScanTime) {
    const auto radarInfo = "Mode: "
        + To::string(operationalMode)
        + ", VCP: "
        + To::string(volumeCoveragePattern)
        + ", " + "Product: "
        + To::string(productCode)
        + ", " + "Height: "
        + To::string(radarHeight);
    const int64_t sec = (((volumeScanDate) - 1) * 3600 * 24) + volumeScanTime;
    auto dateString = ObjectDateTime::getTimeFromPointAsString(sec);
    const auto radarInfoFinal = dateString + " " + radarInfo;
    fileStorage->radarInfo = radarInfoFinal;
    // fileStorage->radarDate = dateString;
    // radarBuffers.fileStorage.radarVcp = volumeCoveragePattern.toString();
    fileStorage->radarAgeMilli = static_cast<int>(ObjectDateTime::currentTimeMillis() - sec * 1000);
    this->radarInfo = radarInfoFinal;
    this->radarAgeMilli = fileStorage->radarAgeMilli;
}
