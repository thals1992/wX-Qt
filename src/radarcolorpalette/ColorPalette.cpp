// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radarcolorpalette/ColorPalette.h"
#include <memory>
#include <string>
#include "objects/WString.h"
#include "radar/UtilityNexradColors.h"
#include "radarcolorpalette/UtilityColorPalette.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityList.h"

unordered_map<int, string> ColorPalette::radarColorPalette;
unordered_map<int, ColorPalette *> ColorPalette::colorMap;

ColorPalette::ColorPalette(int code)
    : redValues{ std::make_unique<MemoryBuffer>(16) }
    , greenValues{ std::make_unique<MemoryBuffer>(16) }
    , blueValues{ std::make_unique<MemoryBuffer>(16) }
    , colorMapCode{ code }
{}

void ColorPalette::setupBuffers(int size) {
    redValues = std::make_unique<MemoryBuffer>(size);
    greenValues = std::make_unique<MemoryBuffer>(size);
    blueValues = std::make_unique<MemoryBuffer>(size);
}

void ColorPalette::position(int position) const {
    redValues->setPosition(position);
    greenValues->setPosition(position);
    blueValues->setPosition(position);
}

void ColorPalette::putBytesViaBytes(unsigned char redByte, unsigned char greenByte, unsigned char blueByte) const {
    redValues->put(redByte);
    greenValues->put(greenByte);
    blueValues->put(blueByte);
}

void ColorPalette::putBytes(const ColorPaletteLine& objectColorPaletteLine) const {
    redValues->put(objectColorPaletteLine.red);
    greenValues->put(objectColorPaletteLine.green);
    blueValues->put(objectColorPaletteLine.blue);
}

// comma separated r,g,b (4bit)
void ColorPalette::putLine(const string& line) const {
    const auto colors = WString::split(line, ",");
    putBytesViaBytes(To::Int(colors[0]), To::Int(colors[1]), To::Int(colors[2]));
}

void ColorPalette::putBytesFromLine(const ColorPaletteLine& objectColorPaletteLine) const {
    redValues->put(objectColorPaletteLine.red);
    greenValues->put(objectColorPaletteLine.green);
    blueValues->put(objectColorPaletteLine.blue);
}

void ColorPalette::putVector(const vector<double>& v) const {
    redValues->put(static_cast<int>(v[0] * 255));
    greenValues->put(static_cast<int>(v[1] * 255));
    blueValues->put(static_cast<int>(v[2] * 255));
}

void ColorPalette::initialize() {
    switch (colorMapCode) {
        case 19:
            setupBuffers(4 * 16);
            generate4bitGeneric(colorMapCode);
            break;
        case 30:
            setupBuffers(4 * 16);
            generate4bitGeneric(colorMapCode);
            break;
        case 56:
            setupBuffers(4 * 16);
            generate4bitGeneric(colorMapCode);
            break;
        case 165:
            setupBuffers(4 * 256);
            loadColorMap165();
            break;
        default:
            // previously this held 256 bytes as each color was represented via byte. Now holds int so 4 times that
            setupBuffers(4 * 256);
            loadColorMap(colorMapCode);
            break;
    }
}

void ColorPalette::generate(int productCode, const string& code) {
    auto objectColorPalette = colorMap[productCode];
    vector<ColorPaletteLine> objectColorPaletteLines;
    auto scale = 0;
    auto lowerEnd = 0;
    auto prodOffset = 0.0;
    auto prodScale = 1.0;
    objectColorPalette->position(0);
    switch (productCode) {
        case 94:
            scale = 2;
            lowerEnd = -32;
            break;
        case 99:
            scale = 1;
            lowerEnd = -127;
            break;
        case 134:
            scale = 1;
            lowerEnd = 0;
            prodOffset = 0.0;
            prodScale = 3.64;
            break;
        case 135:
            scale = 1;
            lowerEnd = 0;
            break;
        case 159:
            scale = 1;
            lowerEnd = 0;
            prodOffset = 128.0;
            prodScale = 16.0;
            break;
        case 161:
            scale = 1;
            lowerEnd = 0;
            prodOffset = -60.5;
            prodScale = 300.0;
            break;
        case 163:
            scale = 1;
            lowerEnd = 0;
            prodOffset = 43.0;
            prodScale = 20.0;
            break;
        case 172:
            scale = 1;
            lowerEnd = 0;
            break;
        default:
            break;
    }
    auto priorLineHas6 = false;
    const auto lines = UtilityColorPalette::getColorMapStringFromDisk(productCode, code);
    for (auto z : range(lines.size())) {
        if (WString::contains(lines[z], "olor") && !WString::contains(lines[z], "#")) {
            const auto items = WString::contains(lines[z], ",") ? WString::split(lines[z], ",") : WString::split(lines[z], " ");
            if (items.size() > 4) {
                const auto& red = items[2];
                const auto& green = items[3];
                const auto& blue = items[4];
                if (priorLineHas6) {
                    objectColorPaletteLines.emplace_back(static_cast<int>(To::Double(items[1]) * prodScale + prodOffset - 1), red, green, blue);
                    objectColorPaletteLines.emplace_back(static_cast<int>(To::Double(items[1]) * prodScale + prodOffset), red, green, blue);
                    priorLineHas6 = false;
                } else {
                    objectColorPaletteLines.emplace_back(static_cast<int>(To::Double(items[1]) * prodScale + prodOffset), red, green, blue);
                }
                if (items.size() > 7) {
                    priorLineHas6 = true;
                }
            }
        }
    }
    if (productCode == 161) {
        for ([[maybe_unused]] auto index : range(10)) {
            objectColorPalette->putBytes(objectColorPaletteLines[0]);
        }
    }
    if (productCode == 99 || productCode == 135) {
        objectColorPalette->putBytes(objectColorPaletteLines[0]);
        objectColorPalette->putBytes(objectColorPaletteLines[0]);
    }
    for ([[maybe_unused]] auto index : range2(lowerEnd, objectColorPaletteLines[0].dbz)) {
        objectColorPalette->putBytes(objectColorPaletteLines[0]);
        if (scale == 2) {
            objectColorPalette->putBytes(objectColorPaletteLines[0]);
        }
    }
    for (auto index : range(objectColorPaletteLines.size())) {
        if (static_cast<size_t>(index) < (objectColorPaletteLines.size() - 1)) {
            const auto low = objectColorPaletteLines[index].dbz;
            const auto lowColor = objectColorPaletteLines[index].asVector();
            const auto high = objectColorPaletteLines[index + 1].dbz;
            const auto highColor = objectColorPaletteLines[index + 1].asVector();
            auto diff = high - low;
            objectColorPalette->putBytes(objectColorPaletteLines[index]);
            if (scale == 2) {
                objectColorPalette->putBytes(objectColorPaletteLines[index]);
            }
            if (diff == 0) {
                diff = 1;
            }
            for (auto j : range2(1, diff)) {
                if (scale == 1) {
                    const auto colorInt = UtilityNexradColors::interpolateColor(lowColor, highColor, static_cast<double>(j) / static_cast<double>(diff * scale));
                    objectColorPalette->putVector(colorInt);
                } else if (scale == 2) {
                    const auto colorInt = UtilityNexradColors::interpolateColor(lowColor, highColor, static_cast<double>(((j * 2) - 1)) / static_cast<double>((diff * 2)));
                    const auto colorInt2 = UtilityNexradColors::interpolateColor(lowColor, highColor, static_cast<double>((j * 2)) / static_cast<double>((diff * 2)));
                    objectColorPalette->putVector(colorInt);
                    objectColorPalette->putVector(colorInt2);
                }
            }
        } else {
            objectColorPalette->putBytes(objectColorPaletteLines[index]);
            if (scale == 2) {
                objectColorPalette->putBytes(objectColorPaletteLines[index]);
            }
        }
    }
}

void ColorPalette::loadColorMap(int productCode) {
    refreshPref();
    generate(productCode, radarColorPalette[productCode]);
}

void ColorPalette::generate4bitGeneric(int product) {
    colorMap[product]->position(0);
    const auto lines = UtilityColorPalette::getColorMapStringFromDisk(product, "CODENH");
    for (const auto& line : lines) {
        if (WString::contains(line, ",")) {
            colorMap[product]->putLine(line);
        }
    }
}

void ColorPalette::loadColorMap165() {
    const auto radarColorPaletteCode = 165;
    vector<ColorPaletteLine> objectColorPaletteLines;
    const auto text = UtilityColorPalette::getColorMapStringFromDisk(radarColorPaletteCode, "CODENH");
    for (const auto& data : text) {
        const auto items = (WString::contains(data, ",")) ? WString::split(data, ",") : WString::split(data, " ");
        if (items.size() > 4) {
            objectColorPaletteLines.emplace_back(items);
        }
    }
    const auto diff = 10;
    for (const auto& objectColorPaletteLine : objectColorPaletteLines) {
        for ([[maybe_unused]] auto j : range(diff)) {
            ColorPalette::colorMap[radarColorPaletteCode]->putBytesFromLine(objectColorPaletteLine);
        }
    }
}

void ColorPalette::refreshPref() {
    radarColorPalette.clear();
    for (auto data : {94, 99, 134, 135, 159, 161, 163, 165, 172}) {
        radarColorPalette[data] = Utility::readPref("RADAR_COLOR_PALETTE_" + To::string(data), "CODENH");
    }
}
