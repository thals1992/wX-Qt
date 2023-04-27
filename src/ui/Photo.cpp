// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "Photo.h"
#include "settings/UIPreferences.h"
#include "util/UtilityForecastIcon.h"
#include "util/UtilityUI.h"

Photo::Photo() = default;

Photo::Photo(QWidget * parent)
    : image{ new QLabel{parent} }
{}

Photo::Photo(QWidget * parent, const QPixmap & pix)
    : image{ new QLabel{parent} }
{
    image->setPixmap(pix);
}

Photo::Photo(QWidget * parent, PhotoSizeEnum size)
    : image{ new QLabel{parent} }
    , size{ size }
    , width{ UtilityUI::getImageWidth(3) }
{}

void Photo::setFullScreen(const QByteArray& ba) {
    const auto pixmap = QPixmap::fromImage(QImage::fromData(reinterpret_cast<const uchar *>(ba.data()), static_cast<int>(ba.size())));
    const auto dimensions = UtilityUI::getScreenBounds();
    if (dimensions[1] > dimensions[0]) {
        const auto pixmapResized = pixmap.scaledToWidth(UtilityUI::getScreenBounds()[0], Qt::SmoothTransformation);
        set(pixmapResized);
    } else {
        const auto pixmapResized = pixmap.scaledToHeight(UtilityUI::getScreenBounds()[1] - 100, Qt::SmoothTransformation);
        set(pixmapResized);
    }
}

void Photo::setNoScale(const QByteArray& ba) {
    const auto pixmap = QPixmap::fromImage(QImage::fromData(ba));
    set(pixmap);
}

void Photo::setToWidth(const QByteArray& ba, int width) {
    const auto pixmap = QPixmap::fromImage(QImage::fromData(ba));
    const auto pixmapResized = pixmap.scaled(width, width, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    set(pixmapResized);
}

void Photo::set(const QPixmap & pix) {
    image->setPixmap(pix);
    image->adjustSize();
}

void Photo::setAlignment(Qt::Alignment alignment) {
    image->setAlignment(alignment);
}

void Photo::setToWidthEven(const QByteArray& ba) {
    UtilityUI::updateImage(getView(), ba, width);
}

void Photo::setBytes(const QByteArray& ba) {
    if (size == Full) {
        setFullScreen(ba);
    } else if (size == Scaled) {
        setToWidth(ba, width);
    } else if (size == Even) {
        setToWidthEven(ba);
    } else {
        setNoScale(ba);
    }
}

void Photo::setNwsIcon(const string& url) {
    const auto width = UIPreferences::imageSizeNwsForecast;
    const auto pixmap = QPixmap::fromImage(UtilityForecastIcon::getIcon(url));
    const auto pixmapResized = pixmap.scaled(width, width, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    getView()->setPixmap(pixmapResized);
}

QLabel * Photo::getView() {
    return image;
}
