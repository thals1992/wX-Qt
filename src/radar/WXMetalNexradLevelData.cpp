// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/WXMetalNexradLevelData.h"
#include <iostream>
#include <vector>
#include "common/GlobalDictionaries.h"
#include "objects/ObjectDateTime.h"
#include "radar/NexradState.h"
#include "radar/UtilityWXMetalPerf.h"
#include "radar/UtilityWXMetalPerfRaster.h"
#include "radar/WXGLNexrad.h"
#include "util/To.h"
#include "util/UtilityList.h"

WXMetalNexradLevelData::WXMetalNexradLevelData(NexradState * nexradState, FileStorage * fileStorge)
    : fileStorage{ fileStorge }
    , numberOfRangeBins{ 916 }
    , numberOfRadials{ 360 }
    , productCode{ static_cast<uint16_t>(GlobalDictionaries::radarProductStringToShortInt.at(nexradState->getRadarProduct())) }
    , nexradState{ nexradState }
{}

void WXMetalNexradLevelData::decode() {
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

void WXMetalNexradLevelData::generateRadials() {
    if (contains({37, 38}, productCode)) {
        totalBins = UtilityWXMetalPerfRaster::generate(&radarBuffers, this);
    } else if (contains({30, 56, 78, 80, 181}, productCode)) {
        totalBins = UtilityWXMetalPerf::genRadials(&radarBuffers);
    } else {
        totalBins = UtilityWXMetalPerf::decode8BitAndGenRadials(&radarBuffers, fileStorage);
    }
}

void WXMetalNexradLevelData::decodeAndPlotNexradLevel3() {
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
        WXGLNexrad::wxoglDspLegendMax = (255.0 / halfWord3132) * 0.01;
        dis->skipBytes(26);
        dis->skipBytes(30);
        seekStart = dis->getPosition();
        binSize = WXGLNexrad::getBinSize(productCode);
        numberOfRangeBins = WXGLNexrad::getNumberRangeBins(productCode);
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

void WXMetalNexradLevelData::decodeAndPlotNexradLevel3FourBit() {
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
            numberOfRangeBins = decodeRaster();
            break;
        case 38:
            numberOfRangeBins = decodeRaster();
            break;
        case 41:
            numberOfRangeBins = decodeRaster();
            break;
        case 57:
            numberOfRangeBins = decodeRaster();
            break;
        default:
            numberOfRangeBins = decodeRadial4bit();
            break;
        }
        binSize = WXGLNexrad::getBinSize(productCode);
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

void WXMetalNexradLevelData::writeTime(uint16_t volumeScanDate, int volumeScanTime) {
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

int WXMetalNexradLevelData::decodeRadial4bit() {
    MemoryBuffer * dis;
    if (radarBuffers.animationIndex == -1) {
        dis = &(fileStorage->memoryBuffer);
        dis->setPosition(0);
    } else {
        dis = &(fileStorage->animationMemoryBuffer[radarBuffers.animationIndex]);
        dis->setPosition(0);
    }
    if (dis->getCapacity() > 0) {
        dis->skipBytes(170);
        auto numberOfRangeBins = dis->getUnsignedShort();
        dis->skipBytes(6);
        dis->getUnsignedShort();
//        uint16_t numberOfRleHalfWords[360];
        radarBuffers.radialStartAngle.setPosition(0);
        for ([[maybe_unused]] auto i : range(360)) {
            auto numberOfRleHalfWord = dis->getUnsignedShort();
            auto rad = static_cast<float>(450.0 - (dis->getUnsignedShort() / 10.0));
            radarBuffers.radialStartAngle.putFloat(rad);
            dis->skipBytes(2);
            for (auto unused1 = 0; unused1 < numberOfRleHalfWord * 2; unused1++) {
                auto bin = dis->get();
                auto numOfBins = static_cast<int>(bin >> 4);
                for (auto unused2 = 0; unused2 < numOfBins; unused2++) {
                    radarBuffers.binWord.put(static_cast<int>(bin % 16));
                }
            }
        }
        return numberOfRangeBins;
    } else {
        return 230;
    }
}

int WXMetalNexradLevelData::decodeRaster() {
    MemoryBuffer * dis;
    if (radarBuffers.animationIndex == -1) {
        dis = &(fileStorage->memoryBuffer);
        dis->setPosition(0);
    } else {
        dis = &(fileStorage->animationMemoryBuffer[radarBuffers.animationIndex]);
        dis->setPosition(0);
    }
    if (dis->getCapacity() > 0) {
        dis->skipBytes(172);
        // let iCoordinateStart = dis.getUnsignedShort()
        // let jCoordinateStart = dis.getUnsignedShort()
        // let xScaleInt = dis.getUnsignedShort()
        // let xScaleFractional = dis.getUnsignedShort()
        // let yScaleInt = dis.getUnsignedShort()
        // let yScaleFractional = dis.getUnsignedShort()
        // let numberOfRows = dis.getUnsignedShort()
        // let packingDescriptor = dis.getUnsignedShort()
        dis->getUnsignedShort();
        dis->getUnsignedShort();
        dis->getUnsignedShort();
        dis->getUnsignedShort();
        dis->getUnsignedShort();
        dis->getUnsignedShort();
        auto numberOfRows = dis->getUnsignedShort();
        dis->getUnsignedShort();
        // 464 rows in NCR
        // 232 rows in NCZ
        for (auto unused0 = 0; unused0 < numberOfRows; unused0++) {
            auto numberOfBytes = dis->getUnsignedShort();
            for (auto unused1 = 0; unused1 < numberOfBytes; unused1++) {
                auto bin = static_cast<int>(dis->get());
                auto numOfBins = static_cast<int>(bin >> 4);
                for (auto unused2 = 0; unused2 < numOfBins; unused2++) {
                    unsigned char color = bin % 16;
                    radarBuffers.binWord.put(color);
                }
            }
        }
    }
    return 0;
}
