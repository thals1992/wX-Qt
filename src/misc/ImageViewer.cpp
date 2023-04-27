// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/ImageViewer.h"

ImageViewer::ImageViewer(QWidget * parent, const QByteArray& imageData)
    : Window{parent}
    , photo { Photo{this, Full} }
{
    photo.setBytes(imageData);
    box.addWidgetAndCenter(photo);
    box.getAndShow(this);
}
