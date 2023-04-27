// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "RadarGeomInfo.h"
#include <array>
#include <cstring>
#include <iostream>
#include "common/GlobalVariables.h"
#include "objects/Color.h"
#include "objects/WString.h"
#include "util/Utility.h"
#include "util/UtilityIO.h"

RadarGeomInfo::RadarGeomInfo() = default;

RadarGeomInfo::RadarGeomInfo(RadarGeometryTypeEnum type)
    : type{ type }
    , isEnabled{ WString::startsWith(Utility::readPref(prefToken.at(type), defaultPref.at(type)), "t") }
{
    if (isEnabled) {
        loadData(typeToFileName.at(type), lineData);
        // colorInt = Utility::readPrefInt(prefTokenColorInt.at(type), prefTokenColorIntDefault.at(type));
        // qcolor = Color::intToQColor(colorInt);
        // lineSize = Utility::readPrefInt(prefTokenLineSize.at(type), lineSizeDefault) / lineFactor;
    } else {
        lineData.clear();
    }
    colorInt = Utility::readPrefInt(prefTokenColorInt.at(type), prefTokenColorIntDefault.at(type));
    qcolor = Color::intToQColor(colorInt);
    lineSize = Utility::readPrefInt(prefTokenLineSize.at(type), lineSizeDefault) / lineFactor;
}

void RadarGeomInfo::update() {
    isEnabled = WString::startsWith(Utility::readPref(prefToken.at(type), defaultPref.at(type)), "t");
    if (isEnabled && lineData.empty()) {
        loadData(typeToFileName.at(type), lineData);
    } else if (!isEnabled) {
        lineData.clear();
    }
    colorInt = Utility::readPrefInt(prefTokenColorInt.at(type), prefTokenColorIntDefault.at(type));
    qcolor = Color::intToQColor(colorInt);
    lineSize = Utility::readPrefInt(prefTokenLineSize.at(type), lineSizeDefault) / lineFactor;
}

const unordered_map<RadarGeometryTypeEnum, string> RadarGeomInfo::typeToFileName{
    {StateLines, "statev2.bin"},
    {CountyLines, "county.bin"},
    {HwLines, "hwv4.bin"},
    {HwExtLines, "hwv4ext.bin"},
    {LakeLines, "lakesv3.bin"},
    {CaLines, "ca.bin"},
    {MxLines, "mx.bin"},
};

const unordered_map<RadarGeometryTypeEnum, string> RadarGeomInfo::prefToken{
    {StateLines, "RADAR_SHOW_STATELINES"},
    {CountyLines, "RADAR_SHOW_COUNTY"},
    {HwLines, "COD_HW_DEFAULT"},
    {HwExtLines, "RADAR_HW_ENH_EXT"},
    {LakeLines, "COD_LAKES_DEFAULT"},
    {CaLines, "RADARCANADALINES"},
    {MxLines, "RADARMEXICOLINES"},
};

const unordered_map<RadarGeometryTypeEnum, string> RadarGeomInfo::defaultPref{
    {StateLines, "true"},
    {CountyLines, "true"},
    {HwLines, "false"},
    {HwExtLines, "false"},
    {LakeLines, "false"},
    {CaLines, "false"},
    {MxLines, "false"},
};

const unordered_map<RadarGeometryTypeEnum, string> RadarGeomInfo::prefTokenLineSize{
    {StateLines, "RADAR_STATE_LINESIZE"},
    {CountyLines, "RADAR_COUNTY_LINESIZE"},
    {HwLines, "RADAR_HW_LINESIZE"},
    {HwExtLines, "RADAR_HWEXT_LINESIZE"},
    {LakeLines, "RADAR_LAKE_LINESIZE"},
    {CaLines, "RADAR_STATE_LINESIZE"},
    {MxLines, "RADAR_STATE_LINESIZE"},
};

const unordered_map<RadarGeometryTypeEnum, string> RadarGeomInfo::prefTokenColorInt{
    {StateLines, "RADAR_COLOR_STATE"},
    {CountyLines, "RADAR_COLOR_COUNTY"},
    {HwLines, "RADAR_COLOR_HW"},
    {HwExtLines, "RADAR_COLOR_HW_EXT"},
    {LakeLines, "RADAR_COLOR_LAKES"},
    {CaLines, "RADAR_COLOR_STATE"},
    {MxLines, "RADAR_COLOR_STATE"},
};

const unordered_map<RadarGeometryTypeEnum, int> RadarGeomInfo::prefTokenColorIntDefault{
    {StateLines, Color::rgb(255, 255, 255)},
    {CountyLines, Color::rgb(75, 75, 75)},
    {HwLines, Color::rgb(135, 135, 135)},
    {HwExtLines, Color::rgb(91, 91, 91)},
    {LakeLines, Color::rgb(0, 0, 255)},
    {CaLines, Color::rgb(255, 255, 255)},
    {MxLines, Color::rgb(255, 255, 255)},
};

void RadarGeomInfo::loadData(const string& fileName, vector<float>& ba) {
    const auto data = UtilityIO::readBinaryFileFromResource(GlobalVariables::resDir + fileName);
    ba.resize(data.size() / 4);
    auto j = 0;
    std::array<unsigned char, 4> c;
    for (int index = 0; index + 3 < data.size(); index += 4) {
        c[0] = data[index + 3];
        c[1] = data[index + 2];
        c[2] = data[index + 1];
        c[3] = data[index];
        // auto f = 0.0f;
        memcpy(&ba[j], c.data(), 4);
        // ba[j] = f;
        j += 1;
    }
}
