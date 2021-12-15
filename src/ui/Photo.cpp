// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "Photo.h"
#include "settings/UIPreferences.h"
#include "util/UtilityNws.h"
#include "util/UtilityUI.h"

Photo::Photo() {
}

Photo::Photo(QWidget * parent) {
    image = new QLabel(parent);
}

Photo::Photo(QWidget * parent, const QPixmap & pix) {
    image = new QLabel(parent);
    image->setPixmap(pix);
}

Photo::Photo(QWidget * parent, PhotoSizeEnum size) {
    image = new QLabel(parent);
    this->size = size;
    width = UtilityUI::getImageWidth(3);
}

void Photo::setFullScreen(const QByteArray& ba) {
    // UtilityUI::updateImageFullScreen(*this, ba);
    const auto pixmap = QPixmap::fromImage(QImage::fromData(reinterpret_cast<const uchar *>(ba.data()), ba.size()));
    const auto pixmapResized = pixmap.scaledToHeight(UtilityUI::getScreenBounds()[1] - 100, Qt::SmoothTransformation);
    set(pixmapResized);
}

void Photo::setNoScale(const QByteArray& ba) {
    // UtilityUI::updateImageNoResize(*this, ba);
    const auto pixmap = QPixmap::fromImage(QImage::fromData(ba));
    set(pixmap);
}

void Photo::setToWidth(const QByteArray& ba, int width) {
    // UtilityUI::updateImage(*this, ba, width);
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
    UtilityUI::updateImage(get(), ba, width);
}

void Photo::setBytes(const QByteArray& ba) {
    if (size == PhotoSizeEnum::full) {
        setFullScreen(ba);
    } else if (size == PhotoSizeEnum::scaled) {
        setToWidth(ba, width);
    } else if (size == PhotoSizeEnum::even) {
        setToWidthEven(ba);
    } else {
        setNoScale(ba);
    }
}

void Photo::setNwsIcon(QString url) {
    // UtilityUI::setImageToIcon(get(), UtilityNws::getIcon(url), UIPreferences::imageSizeNwsForecast);
    const auto width = UIPreferences::imageSizeNwsForecast;
    const auto pixmap = QPixmap::fromImage(UtilityNws::getIcon(url));
    const auto pixmapResized = pixmap.scaled(width, width, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    get()->setPixmap(pixmapResized);
}

QLabel * Photo::get() {
    return image;
}
