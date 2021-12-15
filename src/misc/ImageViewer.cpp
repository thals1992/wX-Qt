// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/ImageViewer.h"

ImageViewer::ImageViewer(QWidget * parent, QByteArray imageData) : Window(parent) {
    box = VBox(this);
    photo = Photo(this, PhotoSizeEnum::full);
    photo.setBytes(imageData);
    box.addWidgetAndCenter(photo.get());
    box.getAndShow(this);
}
