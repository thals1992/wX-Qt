// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

// Given the raw icon URL from NWS, determine if bitmap is on disk or must be created
// input examples
//  https://api.weather.gov/icons/land/day/rain_showers,60/rain_showers,30?size=medium
//  https://api.weather.gov/icons/land/night/bkn?size=medium
//  https://api.weather.gov/icons/land/day/tsra_hi,40?size=medium

#include "util/UtilityNws.h"
#include <QBrush>
#include <QColor>
#include <QFont>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QRect>
#include "common/GlobalVariables.h"
#include "util/UtilityNwsIcon.h"
#include "util/UtilityString.h"

const int UtilityNws::dimensions = 86;
const int UtilityNws::numHeight = 20;
const QFont UtilityNws::font = QFont("Helvetica", 15, QFont::Bold);
const QPen UtilityNws::penForText = QPen(QColor(38, 97, 139));
const QBrush UtilityNws::brushForBar = QBrush(QColor(255, 255, 255, 200), Qt::SolidPattern);

QImage UtilityNws::getIcon(const QString& url) {
    if (url == "NULL" || url == "") {
        return QPixmap(dimensions, dimensions).toImage();
    }
    auto fileName = url;
    fileName = fileName.replace("?size=medium", "");
    fileName = fileName.replace("?size=small", "");
    fileName = fileName.replace("https://api.weather.gov/icons/land/", "");
    fileName = fileName.replace("http://api.weather.gov/icons/land/", "");
    fileName = fileName.replace("day/", "");

    // legacy add
    fileName = fileName.replace("http://forecast.weather.gov/newimages/medium/", "");
    fileName = fileName.replace("https://forecast.weather.gov/newimages/medium/", "");
    fileName = fileName.replace(".png", "");
    fileName = fileName.replace("http://forecast.weather.gov/DualImage.php?", "");
    fileName = fileName.replace("https://forecast.weather.gov/DualImage.php?", "");
    fileName = fileName.replace("&amp", "");
    // legacy add end

    if (fileName.contains("night")) {
        fileName = fileName.replace("night//", "n");
        fileName = fileName.replace("night/", "n");
        fileName = fileName.replace("/", "/n");
    }
    if (UtilityNwsIcon::iconMap.contains(fileName + ".png")) {
        return QImage(GlobalVariables::imageDir + fileName.split("/").back() + ".png");
    } else {
        return parseBitmapString(fileName);
    }
}

// Given one string that does not have a match on disk, decode and return a bitmap with textual labels
// it could be composed of 2 bitmaps with one or more textual labels (if string has a "/" ) or just one bitmap with label
// input examples
//  rain_showers,70/tsra,80
//  ntsra,80
QImage UtilityNws::parseBitmapString(const QString& url) {
    // legacy: i=nsn;j=nsn;ip=60;jp=30
    // legacy add - 2nd condition
    if (url.contains("/") || url.contains(";jp=") || (url.contains("i=") && url.contains("j="))) {
        auto items = url.split("/");
        if (items.size() > 1) {
            return getDualBitmapWithNumbers(items[0], items[1]);
        }
        // legacy add 
        auto urlTmp = url;
        urlTmp = urlTmp.replace("i=", "");
        urlTmp = urlTmp.replace("j=", "");
        urlTmp = urlTmp.replace("ip=", "");
        urlTmp = urlTmp.replace("jp=", "");
        items = urlTmp.split(";");
        if (items.size() > 3) {
            return getDualBitmapWithNumbers(items[0] + items[2], items[1] + items[3]);
        } else if (items.size() > 2) {
            if (url.contains(";jp=")) {
                return getDualBitmapWithNumbers(items[0], items[1] + items[2]);
            } else {
                return getDualBitmapWithNumbers(items[0] + items[2], items[1]);
            }
        } else {
            return getDualBitmapWithNumbers(items[0], items[1]);
        }
        // legacy add end
    }
    return getBitmapWithOneNumber(url);
}

// Given two strings return a custom bitmap made of two bitmaps with optional numeric label
// input examples
//  rain_showers,60 rain_showers,30
//  nrain_showers,80 nrain_showers,70
//  ntsra_hi,40 ntsra_hi
//  bkn rain
QImage UtilityNws::getDualBitmapWithNumbers(const QString& iconLeftString, const QString& iconRightString) {
    auto leftTokens = iconLeftString.split(",");
    auto rightTokens = iconRightString.split(",");
    auto leftNumber = (leftTokens.size() > 1) ? leftTokens[1] : "";
    auto rightNumber = (rightTokens.size() > 1) ? rightTokens[1] : "";
    QString leftWeatherCondition = "";
    QString rightWeatherCondition = "";
    if (leftTokens.size() > 0 && rightTokens.size() > 0) {
        leftWeatherCondition = leftTokens[0];
        rightWeatherCondition = rightTokens[0];
    } else {
        leftWeatherCondition = "";
        rightWeatherCondition = "";
    }

    // legacy add
    if (!iconLeftString.contains(",") && !iconRightString.contains(",")) {
        leftNumber = UtilityString::parse(iconLeftString, ".*?([0-9]+)");
        leftWeatherCondition = UtilityString::parse(iconLeftString, "([a-z_]+)");
        rightNumber = UtilityString::parse(iconRightString, ".*?([0-9]+)");
        rightWeatherCondition = UtilityString::parse(iconRightString, "([a-z_]+)");
    }
    // legacy add end

    auto halfWidth = 42;
    auto bitmapLeft = QImage(GlobalVariables::imageDir + leftWeatherCondition + ".png");
    auto bitmapRight = QImage(GlobalVariables::imageDir + rightWeatherCondition + ".png");
    QPainter painter;
    painter.begin(&bitmapLeft);
    painter.drawImage(43, 0, bitmapRight);
    if (leftNumber != "" && leftNumber != "0") {
        painter.setPen(Qt::NoPen);
        painter.setBrush(brushForBar);
        painter.drawRect(QRect(0, dimensions - numHeight, dimensions / 2, numHeight));
        painter.setFont(font);
        painter.setPen(penForText);
        painter.drawText(bitmapLeft.rect(), Qt::AlignBottom | Qt::AlignLeft, leftNumber + "%");
    }
    if (rightNumber != "" && rightNumber != "0") {
        painter.setPen(Qt::NoPen);
        painter.setBrush(brushForBar);
        painter.drawRect(QRect(dimensions / 2, dimensions - numHeight, dimensions / 2, numHeight));
        painter.setFont(font);
        painter.setPen(penForText);
        painter.drawText(bitmapLeft.rect(), Qt::AlignBottom | Qt::AlignRight, rightNumber + "%");
    }
    painter.setPen(QPen(Qt::white));
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.drawRect(QRect(halfWidth, 0, 2, dimensions));
    return bitmapLeft;
}

// Given one string return a custom bitmap with numeric label
// input examples
// nrain_showers,80
// tsra_hi,40
QImage UtilityNws::getBitmapWithOneNumber(const QString& iconString) {
    auto items = iconString.split(",");
    auto number = (items.size() > 1) ? items[1] : "";
    auto weatherCondition = (items.size() > 0) ? items[0] : "";

    // legacy add
    if (!iconString.contains(",")) {
        number = UtilityString::parse(iconString, ".*?([0-9]+)");
        weatherCondition = UtilityString::parse(iconString, "([a-z_]+)");
    }
    // legacy add end

    auto image = QImage(GlobalVariables::imageDir + weatherCondition + ".png");
    QPainter painter;
    painter.begin(&image);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brushForBar);
    painter.drawRect(QRect(0, dimensions - numHeight, dimensions, numHeight));
    painter.setPen(penForText);
    painter.setFont(font);
    painter.drawText(image.rect(), Qt::AlignBottom | Qt::AlignRight, number + "%");
    return image;
}
