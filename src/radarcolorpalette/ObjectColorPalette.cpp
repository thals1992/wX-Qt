// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radarcolorpalette/ObjectColorPalette.h"
#include "objects/Color.h"
#include "radar/UtilityNexradColors.h"
#include "radarcolorpalette/UtilityColorPalette.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityList.h"

QHash<int, QString> ObjectColorPalette::radarColorPalette;
QHash<int, ObjectColorPalette *> ObjectColorPalette::colorMap;

ObjectColorPalette::ObjectColorPalette(int code) {
    redValues = std::unique_ptr<MemoryBuffer>(new MemoryBuffer(16));
    greenValues = std::unique_ptr<MemoryBuffer>(new MemoryBuffer(16));
    blueValues = std::unique_ptr<MemoryBuffer>(new MemoryBuffer(16));
    colorMapCode = code;
}

void ObjectColorPalette::setupBuffers(int size) {
    redValues = std::unique_ptr<MemoryBuffer>(new MemoryBuffer(size));
    greenValues = std::unique_ptr<MemoryBuffer>(new MemoryBuffer(size));
    blueValues = std::unique_ptr<MemoryBuffer>(new MemoryBuffer(size));
}

void ObjectColorPalette::position(int position) {
    redValues->setPosition(position);
    greenValues->setPosition(position);
    blueValues->setPosition(position);
}

void ObjectColorPalette::putInt(int colorAsInt) {
    redValues->put(Color::red(colorAsInt));
    greenValues->put(Color::green(colorAsInt));
    blueValues->put(Color::blue(colorAsInt));
}

void ObjectColorPalette::putBytesViaBytes(unsigned char redByte, unsigned char greenByte, unsigned char blueByte) {
    redValues->put(redByte);
    greenValues->put(greenByte);
    blueValues->put(blueByte);
}

void ObjectColorPalette::putBytes(const ObjectColorPaletteLine& objectColorPaletteLine) {
    redValues->put(objectColorPaletteLine.red);
    greenValues->put(objectColorPaletteLine.green);
    blueValues->put(objectColorPaletteLine.blue);
}

// comma separated r,g,b (4bit)
void ObjectColorPalette::putLine(const QString& line) {
    const auto colors = line.split(",");
    putBytesViaBytes(To::Int(colors[0]), To::Int(colors[1]), To::Int(colors[2]));
}

void ObjectColorPalette::initialize() {
    switch (colorMapCode) {
        case 19:
        case 30:
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

void ObjectColorPalette::generate(int productCode, const QString& code) {
    auto objectColorPalette = colorMap[productCode];
    QVector<ObjectColorPaletteLine> objectColorPaletteLines;
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
    QString red;
    QString green;
    QString blue;
    auto priorLineHas6 = false;
    const auto lines = UtilityColorPalette::getColorMapStringFromDisk(productCode, code);
    for (auto z : UtilityList::range(lines.size())) {
        if (lines[z].contains("olor") && !lines[z].contains("#")) {
            const QStringList items = lines[z].contains(",") ? lines[z].split(","): lines[z].split(" ");
            if (items.size() > 4) {
                red = items[2];
                green = items[3];
                blue = items[4];
                if (priorLineHas6) {
                    objectColorPaletteLines.push_back(ObjectColorPaletteLine(static_cast<int>(To::Double(items[1]) * prodScale + prodOffset - 1), red, green, blue));
                    objectColorPaletteLines.push_back(ObjectColorPaletteLine(static_cast<int>(To::Double(items[1]) * prodScale + prodOffset), red, green, blue));
                    priorLineHas6 = false;
                } else {
                    objectColorPaletteLines.push_back(ObjectColorPaletteLine(static_cast<int>(To::Double(items[1]) * prodScale + prodOffset), red, green, blue) );
                }
                if (items.size() > 7) {
                    priorLineHas6 = true;
                    red = items[5];
                    green = items[6];
                    blue = items[7];
                }
            }
        }
    }
    if (productCode == 161) {
        for ([[maybe_unused]] auto index : UtilityList::range(10)) {
            objectColorPalette->putBytes(objectColorPaletteLines[0]);
        }
    }
    if (productCode == 99 || productCode == 135) {
        objectColorPalette->putBytes(objectColorPaletteLines[0]);
        objectColorPalette->putBytes(objectColorPaletteLines[0]);
    }
    for ([[maybe_unused]] auto index : UtilityList::range2(lowerEnd, objectColorPaletteLines[0].dbz)) {
        objectColorPalette->putBytes(objectColorPaletteLines[0]);
        if (scale == 2) {
            objectColorPalette->putBytes(objectColorPaletteLines[0]);
        }
    }
    for (auto index : UtilityList::range(objectColorPaletteLines.size())) {
        if (index < (objectColorPaletteLines.size() - 1)) {
            const int low = objectColorPaletteLines[index].dbz;
            const int lowColor = objectColorPaletteLines[index].asInt();
            const int high = objectColorPaletteLines[index + 1].dbz;
            const int highColor = objectColorPaletteLines[index + 1].asInt();
            int diff = high - low;
            objectColorPalette->putBytes(objectColorPaletteLines[index]);
            if (scale == 2) {
                objectColorPalette->putBytes(objectColorPaletteLines[index]);
            }
            if (diff == 0) {
                diff = 1;
            }
            for (auto j : UtilityList::range2(1, diff)) {
                if (scale == 1) {
                    const int colorInt = UtilityNexradColors::interpolateColor(static_cast<int>(lowColor), static_cast<int>(highColor), static_cast<double>(j) / static_cast<double>(diff * scale));
                    objectColorPalette->putInt(colorInt);
                } else if (scale == 2) {
                    const int colorInt = UtilityNexradColors::interpolateColor(static_cast<int>(lowColor), static_cast<int>(highColor), static_cast<double>(((j * 2) - 1)) / static_cast<double>((diff * 2)));
                    const int colorInt2 = UtilityNexradColors::interpolateColor(static_cast<int>(lowColor), static_cast<int>(highColor), static_cast<double>((j * 2)) / static_cast<double>((diff * 2)));
                    objectColorPalette->putInt(colorInt);
                    objectColorPalette->putInt(colorInt2);
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

void ObjectColorPalette::loadColorMap(int productCode) {
    refreshPref();
    auto map = radarColorPalette[productCode];
    generate(productCode, map);
}

void ObjectColorPalette::generate4bitGeneric(int product) {
    colorMap[product]->position(0);
    const auto lines = UtilityColorPalette::getColorMapStringFromDisk(product, "CODENH");
    for (const auto& line : lines) {
        if (line.contains(",")) {
            colorMap[product]->putLine(line);
        }
    }
}

void ObjectColorPalette::loadColorMap165() {
    const auto radarColorPaletteCode = 165;
    QVector<ObjectColorPaletteLine> objectColorPaletteLines;
    const auto text = UtilityColorPalette::getColorMapStringFromDisk(radarColorPaletteCode, "CODENH");
    for (const auto& data : text) {
        const auto items = (data.contains(',')) ? data.split(',') : data.split(' ');
        if (items.size() > 4) {
            objectColorPaletteLines.push_back(ObjectColorPaletteLine(items));
        }
    }
    const int diff = 10;
    for (auto i : UtilityList::range(objectColorPaletteLines.size())) {
        for ([[maybe_unused]] auto j : UtilityList::range(diff)) {
            colorMap[radarColorPaletteCode]->putInt(objectColorPaletteLines[i].asInt());
        }
    }
}

void ObjectColorPalette::refreshPref() {
    radarColorPalette.clear();
    const QVector<int> radarProductCodes = {94, 99, 134, 135, 159, 161, 163, 165, 172};
    for (auto data : radarProductCodes) {
        radarColorPalette[data] = Utility::readPref("RADAR_COLOR_PALETTE_" + To::String(data), "CODENH");
    }
}
