// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "RadarGeometry.h"

unordered_map<RadarGeometryTypeEnum, RadarGeomInfo> RadarGeometry::dataByType;

void RadarGeometry::initialize() {
    for (auto t : {
        StateLines,
        CountyLines,
        HwLines,
        HwExtLines,
        LakeLines,
        CaLines,
        MxLines,
    }) {
        if (dataByType.contains(t)) {
            dataByType[t].update();
        } else {
            dataByType[t] = RadarGeomInfo{t};
        }
    }
}
