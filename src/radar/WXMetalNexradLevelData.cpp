// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/WXMetalNexradLevelData.h"
#include <QDateTime>
#include <QVector>
#include <iostream>
#include "common/GlobalDictionaries.h"
#include "radar/UtilityWXMetalPerf.h"
#include "radar/UtilityWXMetalPerfRaster.h"
#include "radar/WXGLNexrad.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityTime.h"

WXMetalNexradLevelData::WXMetalNexradLevelData() {
}

WXMetalNexradLevelData::WXMetalNexradLevelData(const QString& product, ObjectMetalRadarBuffers * buff, const QString& idx) {
    radialStartAngle = MemoryBuffer();
    binSize = 0.0;
    numberOfRangeBins = 916;
    numberOfRadials = 360;
    binWord = MemoryBuffer();
    productCode = 0;
    halfWord3132 = 0.0;
    timestampStr = "";
    seekStart = 0;
    compressedFileSize = 0;
    radarHeight = 0;
    degree = 0.0;
    operationalMode = 0;
    volumeCoveragePattern = 0;
    latitudeOfRadar = 0.0;
    longitudeOfRadar = 0.0;
    sequenceNumber = 0;
    volumeScanNumber = 0;
    elevationNumber = 0;
    volumeScanDate = 0;
    volumeScanTime = 0;
    elevationAngle = 0;
    radarBuffers = buff;
    index = idx;
    productCode = GlobalDictionaries::radarProductStringToShortInt[product];
}

void WXMetalNexradLevelData::decode() {
    switch (productCode) {
        case 153:
        case 154:
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

void WXMetalNexradLevelData::decodeAndPlotNexradLevel3() {
    MemoryBuffer * dis;
    if (radarBuffers->animationIndex == -1) {
        dis = &(radarBuffers->fileStorage->memoryBuffer);
    } else {
        dis = &(radarBuffers->fileStorage->animationMemoryBuffer[radarBuffers->animationIndex]);
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

        radarBuffers->numberOfRangeBins = numberOfRangeBins;
        radarBuffers->numberOfRadials = numberOfRadials;
        radarBuffers->binSize = binSize;
        radarBuffers->productCode = productCode;
    }
}

void WXMetalNexradLevelData::decodeAndPlotNexradLevel3FourBit() {
    switch (productCode) {
        case 181:
            binWord = MemoryBuffer(360 * 720);
            break;
        case 78:
        case 80:
            binWord = MemoryBuffer(360 * 592);
            break;
        case 37:
        case 38:
            binWord = MemoryBuffer(464 * 464);
            break;
        default:
            binWord = MemoryBuffer(360 * 230);
            break;
    }
    radialStartAngle = MemoryBuffer(4 * 360);
    MemoryBuffer * dis;
    if (radarBuffers->animationIndex == -1) {
        dis = &(radarBuffers->fileStorage->memoryBuffer);
    } else {
        dis = &(radarBuffers->fileStorage->animationMemoryBuffer[radarBuffers->animationIndex]);
        dis->setPosition(0);
    }
    if (dis->getCapacity() > 0) {
        dis->skipBytes(30);
        dis->skipBytes(20);
        dis->skipBytes(8);
        [[maybe_unused]] int radarHeight = dis->getUnsignedShort();
        int16_t productCode = dis->getUnsignedShort();
        [[maybe_unused]] int16_t operationalMode = dis->getUnsignedShort();
        volumeCoveragePattern = dis->getUnsignedShort();
        sequenceNumber = dis->getUnsignedShort();
        volumeScanNumber = dis->getUnsignedShort();
        int16_t volumeScanDate = dis->getUnsignedShort();
        int volumeScanTime = dis->getInt();
        writeTime(volumeScanDate, volumeScanTime);
        dis->skipBytes(6);
        dis->skipBytes(56);
        dis->skipBytes(32);
        switch (productCode) {
        case 37:
        case 38:
        case 41:
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
    radarBuffers->numberOfRangeBins = numberOfRangeBins;
    radarBuffers->numberOfRadials = numberOfRadials;
    radarBuffers->binSize = binSize;
    radarBuffers->productCode = productCode;
}

void WXMetalNexradLevelData::writeTime(int16_t volumeScanDate, int volumeScanTime) const {
    const auto radarInfo = "Mode: " + To::String(operationalMode) + ", VCP: " + To::String(volumeCoveragePattern)
            + ", " + "Product: " + To::String(productCode) + ", " + "Height: " + To::String(radarHeight);
    const int64_t sec = (((volumeScanDate) - 1) * 3600 * 24) + volumeScanTime;
    const auto radarTime = QDateTime::fromMSecsSinceEpoch(sec * 1000);
    const auto dateString = radarTime.toString("hh:mm:ss");
    const auto radarInfoFinal = dateString + " " + radarInfo;
    //WXGLNexrad::writeRadarInfo(radarInfoFinal, index);
    Utility::writePref("WXRADAR_CURRENT_MILLI" + index, To::String(static_cast<int>(UtilityTime::currentTimeMillis() - sec * 1000)));

    radarBuffers->fileStorage->radarInfo = radarInfoFinal;
    radarBuffers->fileStorage->radarDate = dateString;
    //radarBuffers->fileStorage.radarVcp = volumeCoveragePattern.toString();
    radarBuffers->fileStorage->radarAgeMilli = static_cast<int>(UtilityTime::currentTimeMillis() - sec * 1000);
}

int WXMetalNexradLevelData::generateRadials() {
    const QVector<int> rasterProducts = {37, 38};
    const QVector<int> noDecode = {153, 154, 30, 56, 78, 80, 181};
    auto totalBins = 0;
    if (rasterProducts.contains(productCode)) {
        totalBins = UtilityWXMetalPerfRaster::generate(this);
    } else if (noDecode.contains(productCode)) {
        totalBins = UtilityWXMetalPerf::genRadials(radarBuffers, this);
    } else {
        totalBins = UtilityWXMetalPerf::decode8BitAndGenRadials(radarBuffers, this);
    }
    return totalBins;
}


int WXMetalNexradLevelData::decodeRadial4bit() {
    MemoryBuffer * dis;
    if (radarBuffers->animationIndex == -1) {
        dis = &(radarBuffers->fileStorage->memoryBuffer);
        dis->setPosition(0);
    } else {
        dis = &(radarBuffers->fileStorage->animationMemoryBuffer[radarBuffers->animationIndex]);
        dis->setPosition(0);
    }
    if (dis->getCapacity() > 0) {
        dis->skipBytes(170);
        uint16_t numberOfRangeBins = dis->getUnsignedShort();
        dis->skipBytes(6);
        dis->getUnsignedShort();
        uint16_t numberOfRleHalfWords[360];
        radialStartAngle.setPosition(0);
        for (int radial = 0; radial < 360; radial++) {
            numberOfRleHalfWords[radial] = dis->getUnsignedShort();
            radialStartAngle.putFloat((450.0 - (dis->getUnsignedShort() / 10)));
            dis->skipBytes(2);
            for (int unused1 = 0; unused1 < numberOfRleHalfWords[radial] * 2; unused1++) {
                int bin = dis->get();
                int numOfBins = static_cast<int>(bin >> 4);
                for (int unused2 = 0; unused2 < numOfBins; unused2++) {
                    binWord.put(static_cast<int>(bin % 16));
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
    if (radarBuffers->animationIndex == -1) {
        dis = &(radarBuffers->fileStorage->memoryBuffer);
        dis->setPosition(0);
    } else {
        dis = &(radarBuffers->fileStorage->animationMemoryBuffer[radarBuffers->animationIndex]);
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
        uint16_t numberOfRows = dis->getUnsignedShort();
        dis->getUnsignedShort();
        // 464 rows in NCR
        // 232 rows in NCZ
        for (int unused0 = 0; unused0 < numberOfRows; unused0++) {
            uint16_t numberOfBytes = dis->getUnsignedShort();
            for (int unused1 = 0; unused1 < numberOfBytes; unused1++) {
                int bin = dis->get();
                int numOfBins = static_cast<int>(bin >> 4);
                for (int unused2 = 0; unused2 < numOfBins; unused2++) {
                    unsigned char color = bin % 16;
                    binWord.put(color);
                }
            }
        }
    }
    return 0;
}
