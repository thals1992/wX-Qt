// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/WXGLNexrad.h"

float WXGLNexrad::wxoglDspLegendMax = 1.0;

const QStringList WXGLNexrad::radarProductList = {
    "N0Q: Base Reflectivity",
    "N0U: Base Velocity",
    "EET: Enhanced Echo Tops",
    "DVL: Vertically Integrated Liquid",
    "N0C: Correlation Coefficient",
    "N0X: Differential Reflectivity",
    "N0K: Specific Differential Phase",
    "H0C: Hydrometer Classification",
    "DSP: Digital Storm Total Precipitation",
    "DAA: Digital Accumulation Array",
    "N0S: Storm Relative Mean Velocity",
    "NSW: Base Spectrum Width",
    "NCR: Composite Reflectivity 124nm",
    "NCZ: Composite Reflectivity 248nm"
};

const QStringList WXGLNexrad::radarProductListTdwr = {
    "TZL: Long Range Digital Base Reflectivity",
    "TZ0: Digital Base Reflectivity",
    "TV0: Digital Base Velocity",
};

// cat /tmp/a | sed 's/"/"/' | sed 's/,/);/'

double WXGLNexrad::getBinSize(int16_t productCode) {
    const auto binSize54 = 2.0;
    const auto binSize13 = 0.50;
    const auto binSize08 = 0.295011;
    const auto binSize16 = 0.590022;
    const auto binSize110 = 2.0 * binSize54;
    switch (productCode) {
        case 134:
            return binSize54;
        case 135:
            return binSize54;
        case 186:
            return binSize16;
        case 159:
            return binSize13;
        case 161:
            return binSize13;
        case 163:
            return binSize13;
        case 165:
            return binSize13;
        case 99:
            return binSize13;
        case 170:
            return binSize13;
        case 172:
            return binSize13;
        case 180:
        case 181:
        case 182:
            return binSize08;
        case 153:
            return binSize13;
        case 154:
            return binSize13;
        case 155:
            return binSize13;
        case 2161:
            return binSize13;
        case 78:
        case 80:
            return binSize110;
        default:
            return binSize54;
    }
}

int WXGLNexrad::getNumberRangeBins(int16_t productCode) {
    switch (productCode) {
        case 78:
        case 80:
            return 592;
        case 134:
            return 460;
        case 186:
            return 1390;
        case 180:
        case 181:
        case 182:
            return 720;
        case 135:
            return 1200;
        case 99:
            return 1200;
        case 159:
            return 1200;
        case 161:
            return 1200;
        case 163:
            return 1200;
        case 170:
            return 1200;
        case 172:
            return 1200;
        default:
            return 460;
    }
}

bool WXGLNexrad::isProductTdwr(const QString& product) {
    return product.startsWith("TV") || product == "TZL" || product.startsWith("TZ");
}
