// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Image.h"
#include <QObject>
#include "util/UtilityUI.h"

Image::Image() = default;

Image::Image(QWidget * parent)
    : imageSize{ UtilityUI::getImageWidth(3) }
    , parent{ parent }
    , image{ new ClickableLabel{parent} }
{}

ClickableLabel * Image::getView() {
    return image;
}

void Image::setNumberAcross(int num) {
    imageSize = UtilityUI::getImageWidth(num);
}

void Image::connect(const function<void()>& fn) {
    QObject::connect(image, &ClickableLabel::clicked, parent, fn);
}

void Image::setBytes(const QByteArray& imageData) {
    UtilityUI::updateImage(image, imageData, imageSize);
}

void Image::setToWidth(const QByteArray& imageData, int width) {
    image->setToWidth(imageData, width);
}
