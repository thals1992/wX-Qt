// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/UIColorLegend.h"
#include <QColor>
#include <QDebug>
#include <QPoint>
#include <QRect>
#include "objects/Color.h"
#include "radar/WXGLNexrad.h"
#include "radarcolorpalette/ObjectColorPalette.h"
#include "util/To.h"
#include "util/UtilityList.h"
#include "ui/TextViewMetal.h"

UIColorLegend::UIColorLegend(const QString& product) {
    this->product = product;
    color = 0;
    scale = 1.0;
}

void UIColorLegend::drawRect(QPainter * painter, float x, float y, float width, float height) {
    const auto qColor = Color::intToQColor(color);
    painter->setPen(qColor);
    painter->setBrush(QBrush(qColor, Qt::SolidPattern));
    const QPoint point1 = QPoint(x, y);
    const QPoint point2 = QPoint(width, height);
    const QRect rect = QRect(point1, point2);
    painter->drawRect(rect);
}

void UIColorLegend::drawText(QPainter * painter, const QString& stringValue, float x, float y) {
    painter->setFont(qfont);
    painter->setPen(QColor(Qt::white));
    painter->drawText(x, y, stringValue);
}

int UIColorLegend::setColor(int red, int green, int blue) {
    return Color::rgb(red, green, blue);
}

void UIColorLegend::setColorWithBuffers(int prodId, int index) {
    color = setColor(
        ObjectColorPalette::colorMap[prodId]->redValues->getByIndex(index),
        ObjectColorPalette::colorMap[prodId]->greenValues->getByIndex(index),
        ObjectColorPalette::colorMap[prodId]->blueValues->getByIndex(index));
}

void UIColorLegend::paintEvent(QPainter & painter, float zoom, float xPos) {
    // qDebug() << painter.window().topLeft().x() << " " << painter.window().topLeft().y();
    // qDebug() << painter.viewport().topLeft().x() << painter.viewport().bottomRight().y();

    qfont = painter.font();
    qfont.setPixelSize(static_cast<int>(TextViewMetal::fontSize / zoom));

    QString units;
    screenHeight = 0;
    float startHeight = painter.window().topLeft().x() / 2.0;
    // float startHeight = painter.window().topLeft().x();

    float width = 15.0 / zoom;
    float widthStarting = painter.window().topLeft().x() / zoom - xPos / zoom;
    float textFromLegend = 10.0;
    float heightFudge = 15.0;
    float scaledHeight = 1.0 / zoom;
    float scaledHeightText = 0.66 * ((screenHeight - 1.45 * startHeight) / (95.0 + 32.0)) / zoom;
    float scaledHeightVel = 0.66 * ((screenHeight - 1.45 * startHeight) / (127.0 * 2.0)) / zoom;
    bool unitsDrawn = false;
    if (product == "N0Q" || product == "L2REF" || product == "TZL") {
        for (auto index : UtilityList::range(256)) {
            setColorWithBuffers(94, 255 - index);
            drawRect(
                &painter,
                widthStarting,
                (index) * scaledHeight + startHeight,
                width + widthStarting,
                (index) * scaledHeight + scaledHeight + startHeight);
        }
        units = " dBZ";
        for (auto index = 96; index > 1; index--) {
            if (index % 10 == 0) {
                drawText(&painter,
                    To::String(index) + units,
                    widthStarting + width + textFromLegend,
                    (scaledHeightText * ((95) - (index))) + heightFudge + startHeight);
                if (!unitsDrawn) {
                    unitsDrawn = true;
                    units = "";
                }
            }
        }
    } else if (product == "N0U" || product == "L2VEL" || product == "TV0") {
        for (auto index : UtilityList::range(256)) {
            setColorWithBuffers(99, 255 - index);
            drawRect(
                &painter,
                widthStarting,
                (index) * scaledHeight + startHeight,
                width + widthStarting,
                (index) * scaledHeight + scaledHeight + startHeight);
        }
        units = " KT";
        for (int index = 123; index > -131; index--) {
            if (index % 10 == 0) {
                drawText(
                    &painter,
                    To::String(index) + units,
                    widthStarting + width + textFromLegend,
                    (scaledHeightVel * (122.0 - (index))) + heightFudge + startHeight);
                if (!unitsDrawn) {
                    unitsDrawn = true;
                    units = "";
                }
            }
        }
    } else if (product == "DVL") {
        for (auto index : UtilityList::range(256)) {
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
                    To::String(index) + units,
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
        for (auto index : UtilityList::range(71)) {
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
                    To::String(index) + units,
                    widthStarting + width + textFromLegend,
                    (3.64 * scaledHeightVel * (70.0 - index)) + heightFudge + startHeight);
                if (!unitsDrawn) {
                    unitsDrawn = true;
                    units = "";
                }
            }
        }
    } else if (product == "N0X") {
        for (auto index : UtilityList::range(256)) {
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
                To::String(index) + units,
                widthStarting + width + textFromLegend,
                (16 * scaledHeightVel * (8.0 - index)) + heightFudge + startHeight);
            if (!unitsDrawn) {
                unitsDrawn = true;
                units = "";
            }
        }
    } else if (product == "N0C") {
        for (auto index : UtilityList::range(256)) {
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
                QString tmpStr = To::String(index / 100.0);
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
        for (auto index : UtilityList::range(256)) {
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
                To::String(index) + units,
                widthStarting + width + textFromLegend,
                (20.0 * scaledHeightVel * (10.0 - index)) + heightFudge + startHeight);
            if (!unitsDrawn) {
                unitsDrawn = true;
                units = "";
            }
        }
    } else if (product == "H0C") {
        // scaledHeight = (screenHeight - 2.0 * startHeight) / 160.0;
        const QStringList labels = {"ND", "BI", "GC", "IC", "DS", "WS", "RA", "HR", "BD", "GR", "HA", "", "", "", "UK", "RF"};
        for (auto index : UtilityList::range(160)) {
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
        for (auto index : UtilityList::range(256)) {
            setColorWithBuffers(172, 255 - index);
            drawRect(
                &painter,
                widthStarting,
                index * scaledHeight + startHeight,
                width + widthStarting,
                index * scaledHeight + scaledHeight + startHeight);
        }
        units = " IN";
        float j = WXGLNexrad::wxoglDspLegendMax;
        while (j > 0) {
            float xVar = widthStarting + width + textFromLegend;
            float yVar1 = (255.0 / WXGLNexrad::wxoglDspLegendMax) * scaledHeightVel * (WXGLNexrad::wxoglDspLegendMax - j);
            float yVar = yVar1 + heightFudge + startHeight;
            drawText(&painter, To::String(j) + units, xVar, yVar);
            if (!unitsDrawn) {
                unitsDrawn = true;
                units = "";
            }
            j -= WXGLNexrad::wxoglDspLegendMax / 16.0;
        }
    } else if (product == "DAA") {
        for (auto index : UtilityList::range(256)) {
            setColorWithBuffers(172, 255 - index);
            drawRect(
                &painter,
                widthStarting,
                index * scaledHeight + startHeight,
                width + widthStarting,
                index * scaledHeight + scaledHeight + startHeight);
        }
        units = " IN";
        float j = WXGLNexrad::wxoglDspLegendMax;
        while (j > 0) {
            float xVar = widthStarting + width + textFromLegend;
            float yVar1 = (255.0 / WXGLNexrad::wxoglDspLegendMax) * scaledHeightVel * (WXGLNexrad::wxoglDspLegendMax - j);
            float yVar = yVar1 + heightFudge + startHeight;
            drawText(&painter, To::String(j) + units, xVar, yVar);
            if (!unitsDrawn) {
                unitsDrawn = true;
                units = "";
            }
            j -= WXGLNexrad::wxoglDspLegendMax / 16.0;
        }
    }
    painter.end();
}
