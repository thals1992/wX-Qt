// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UIColorLegend.h"
#include <QColor>
#include <QPoint>
#include <QRect>
#include <QString>
#include <vector>
#include "objects/Color.h"
#include "objects/WString.h"
#include "radar/NexradUtil.h"
#include "radarcolorpalette/ColorPalette.h"
#include "util/To.h"
#include "util/UtilityList.h"
#include "ui/TextViewMetal.h"

UIColorLegend::UIColorLegend(const string& product)
    : product{ product }
{}

void UIColorLegend::update(const string& product) {
    this->product = WString::split(product, ":")[0];
}

void UIColorLegend::drawRect(QPainter * painter, double x, double y, double width, double height) const {
    const auto qColor = Color::intToQColor(color);
    painter->setPen(qColor);
    painter->setBrush(QBrush{qColor, Qt::SolidPattern});
    const auto point1 = QPointF{x, y};
    const auto point2 = QPointF{width, height};
    const auto rect = QRectF{point1, point2};
    painter->drawRect(rect);
}

void UIColorLegend::drawText(QPainter * painter, const string& stringValue, double x, double y) {
    painter->setFont(qfont);
    painter->setPen(QColor{Qt::white});
    painter->drawText(static_cast<int>(x), static_cast<int>(y), QString::fromStdString(stringValue));
}

int UIColorLegend::setColor(int red, int green, int blue) {
    return Color::rgb(red, green, blue);
}

void UIColorLegend::setColorWithBuffers(int prodId, int index) {
    color = setColor(
        ColorPalette::colorMap[prodId]->redValues->getByIndex(index),
        ColorPalette::colorMap[prodId]->greenValues->getByIndex(index),
        ColorPalette::colorMap[prodId]->blueValues->getByIndex(index));
}

void UIColorLegend::paintEvent(QPainter & painter, double zoom, double xPos, double yPos) {
    qfont = painter.font();
    qfont.setPointSizeF(TextViewMetal::fontSize / zoom);
    string units;
    screenHeight = 0;
    const auto startHeight = painter.window().topLeft().x() / zoom + 300.0 / zoom - yPos / zoom;
    const auto width = 15.0 / zoom;
    const auto widthStarting = painter.window().topLeft().x() / zoom - xPos / zoom;
    const auto textFromLegend = 10.0 / zoom;
    const auto heightFudge = 15.0 / zoom;
    auto scaledHeight = 1.5 / zoom;
    const auto scaledHeightText = 2.85 / zoom;
    const auto scaledHeightVel = 2.85 * 0.5 / zoom;
    auto unitsDrawn = false;
    if (product == "N0Q" || product == "L2REF" || product == "TZL") {
        for (auto index : range(256)) {
            setColorWithBuffers(94, 255 - index);
            drawRect(
                &painter,
                widthStarting,
                index * scaledHeight + startHeight,
                width + widthStarting,
                index * scaledHeight + scaledHeight + startHeight);
        }
        units = " dBZ";
        for (auto index = 96; index > 1; index--) {
            if (index % 10 == 0) {
                drawText(&painter,
                    To::string(index) + units,
                    widthStarting + width + textFromLegend,
                    scaledHeightText * (95 - index) + heightFudge + startHeight);
                if (!unitsDrawn) {
                    unitsDrawn = true;
                    units = "";
                }
            }
        }
    } else if (product == "N0U" || product == "L2VEL" || product == "TV0") {
        for (auto index : range(256)) {
            setColorWithBuffers(99, 255 - index);
            drawRect(
                &painter,
                widthStarting,
                index * scaledHeight + startHeight,
                width + widthStarting,
                index * scaledHeight + scaledHeight + startHeight);
        }
        units = " KT";
        for (int index = 123; index > -131; index--) {
            if (index % 10 == 0) {
                drawText(
                    &painter,
                    To::string(index) + units,
                    widthStarting + width + textFromLegend,
                    (scaledHeightVel * (122.0 - (index))) + heightFudge + startHeight);
                if (!unitsDrawn) {
                    unitsDrawn = true;
                    units = "";
                }
            }
        }
    } else if (product == "DVL") {
        for (auto index : range(256)) {
            setColorWithBuffers(134, 255 - index);
            drawRect(
                &painter,
                widthStarting,
                index * scaledHeight + startHeight,
                width + widthStarting,
                index * scaledHeight + scaledHeight + startHeight);
        }
        units = " kg/m2";
        for (int index = 71; index > -1; index--) {
            if (index % 5 == 0) {
                drawText(
                    &painter,
                    To::string(index) + units,
                    widthStarting + width + textFromLegend,
                    (3.64 * scaledHeightVel * (70.0 - index)) + heightFudge + startHeight);
                if (!unitsDrawn) {
                    unitsDrawn = true;
                    units = "";
                }
            }
        }
    } else if (product == "EET") {
        scaledHeight = ((screenHeight - 1.45 * startHeight) / 70.0) / zoom;
        for (auto index : range(71)) {
            setColorWithBuffers(135, 70 - index);
            drawRect(
                &painter,
                widthStarting,
                index * scaledHeight + startHeight,
                width + widthStarting, index * scaledHeight + scaledHeight + startHeight);
        }
        units = " K FT";
        for (int index = 71; index > 1; index--) {
            if (index % 5 == 0) {
                drawText(
                    &painter,
                    To::string(index) + units,
                    widthStarting + width + textFromLegend,
                    (3.64 * scaledHeightVel * (70.0 - index)) + heightFudge + startHeight);
                if (!unitsDrawn) {
                    unitsDrawn = true;
                    units = "";
                }
            }
        }
    } else if (product == "N0X") {
        for (auto index : range(256)) {
            setColorWithBuffers(159, 255 - index);
            drawRect(
                &painter,
                widthStarting,
                index * scaledHeight + startHeight,
                width + widthStarting,
                index * scaledHeight + scaledHeight + startHeight);
        }
        units = " dB";
        for (int index = 8; index >= -7; index--) {
            drawText(
                &painter,
                To::string(index) + units,
                widthStarting + width + textFromLegend,
                (16 * scaledHeightVel * (8.0 - index)) + heightFudge + startHeight);
            if (!unitsDrawn) {
                unitsDrawn = true;
                units = "";
            }
        }
    } else if (product == "N0C") {
        for (auto index : range(256)) {
            setColorWithBuffers(161, 255 - index);
            drawRect(
                &painter,
                widthStarting,
                index * scaledHeight + startHeight,
                width + widthStarting,
                index * scaledHeight + scaledHeight + startHeight);
        }
        units = " CC";
        for (int index = 101; index >= 0; index--) {
            if (index % 5 == 0) {
                string tmpStr = To::string(index / 100.0);
                drawText(
                    &painter,
                    tmpStr + units,
                    widthStarting + width + textFromLegend,
                    (3.0 * scaledHeightVel * (100.0 - index)) + heightFudge + startHeight);
                if (!unitsDrawn) {
                    unitsDrawn = true;
                    units = "";
                }
            }
        }
    } else if (product == "N0K") {
        for (auto index : range(256)) {
            setColorWithBuffers(163, 255 - index);
            drawRect(
                &painter,
                widthStarting,
                index * scaledHeight + startHeight,
                width + widthStarting,
                index * scaledHeight + scaledHeight + startHeight);
        }
        units = " PHAS";
        for (int index = 11; index >= -1; index--) {
            drawText(
                &painter,
                To::string(index) + units,
                widthStarting + width + textFromLegend,
                (20.0 * scaledHeightVel * (10.0 - index)) + heightFudge + startHeight);
            if (!unitsDrawn) {
                unitsDrawn = true;
                units = "";
            }
        }
    } else if (product == "H0C") {
        const vector<string> labels = {"ND", "BI", "GC", "IC", "DS", "WS", "RA", "HR", "BD", "GR", "HA", "", "", "", "UK", "RF"};
        for (auto index : range(160)) {
            setColorWithBuffers(165, 160 - index);
            drawRect(
                &painter,
                widthStarting,
                index * scaledHeight + startHeight,
                width + widthStarting,
                index * scaledHeight + scaledHeight + startHeight);
        }
        units = "";
        for (int index = 159; index >= 0; index--) {
            if (index % 10 == 0) {
                drawText(
                    &painter,
                    labels[static_cast<int>(index / 10)] + units,
                    widthStarting + width + textFromLegend,
                    (scaledHeight * (159.0 - index)) + startHeight);
                if (!unitsDrawn) {
                    unitsDrawn = true;
                    units = "";
                }
            }
        }
    } else if (product == "DSP") {
        for (auto index : range(256)) {
            setColorWithBuffers(172, 255 - index);
            drawRect(
                &painter,
                widthStarting,
                index * scaledHeight + startHeight,
                width + widthStarting,
                index * scaledHeight + scaledHeight + startHeight);
        }
        units = " IN";
        double j = NexradUtil::wxoglDspLegendMax;
        while (j > 0) {
            double xVar = widthStarting + width + textFromLegend;
            double yVar1 = (255.0 / NexradUtil::wxoglDspLegendMax) * scaledHeightVel * (NexradUtil::wxoglDspLegendMax - j);
            double yVar = yVar1 + heightFudge + startHeight;
            drawText(&painter, To::string(j) + units, xVar, yVar);
            if (!unitsDrawn) {
                unitsDrawn = true;
                units = "";
            }
            j -= NexradUtil::wxoglDspLegendMax / 16.0;
        }
    } else if (product == "DAA") {
        for (auto index : range(256)) {
            setColorWithBuffers(172, 255 - index);
            drawRect(
                &painter,
                widthStarting,
                index * scaledHeight + startHeight,
                width + widthStarting,
                index * scaledHeight + scaledHeight + startHeight);
        }
        units = " IN";
        double j = NexradUtil::wxoglDspLegendMax;
        while (j > 0) {
            double xVar = widthStarting + width + textFromLegend;
            double yVar1 = (255.0 / NexradUtil::wxoglDspLegendMax) * scaledHeightVel * (NexradUtil::wxoglDspLegendMax - j);
            double yVar = yVar1 + heightFudge + startHeight;
            drawText(&painter, To::string(j) + units, xVar, yVar);
            if (!unitsDrawn) {
                unitsDrawn = true;
                units = "";
            }
            j -= NexradUtil::wxoglDspLegendMax / 16.0;
        }
    }
    painter.end();
}
