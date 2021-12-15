// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Image.h"
#include <QObject>
#include "util/UtilityUI.h"

Image::Image() {
}

Image::Image(QWidget * parent) {
    this->parent = parent;
    image = new ClickableLabel(parent);
    imageSize = UtilityUI::getImageWidth(3);
}

Image Image::withIndex(QWidget * parent, int index) {
    auto img = Image(parent);
    img.index = index;
    return img;
}

ClickableLabel * Image::get() {
    return image;
}

void Image::setNumberAcross(int num) {
    imageSize = UtilityUI::getImageWidth(num);
}

void Image::connect(std::function<void()> fn) {
    QObject::connect(image, &ClickableLabel::clicked, parent, fn);
}

void Image::setBytes(QByteArray imageData) {
    UtilityUI::updateImage(image, imageData, imageSize);
}

void Image::setToWidth(QByteArray imageData, int width) {
    image->setToWidth(imageData, width);
}
