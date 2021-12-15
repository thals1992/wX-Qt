// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include "ui/Photo.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class ImageViewer: public Window {
public:
    ImageViewer(QWidget *, QByteArray);

private:
    Photo photo;
    VBox box;
};

#endif  // IMAGEVIEWER_H
