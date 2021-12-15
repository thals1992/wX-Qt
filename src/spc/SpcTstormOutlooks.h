// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCTSTORMOUTLOOKS_H
#define SPCTSTORMOUTLOOKS_H

#include "ui/HBox.h"
#include "ui/Window.h"

class SpcTstormOutlooks : public Window {
public:
    explicit SpcTstormOutlooks(QWidget *);

private:
    HBox box;
    QVector<Image> images;
    QStringList urls;
};

#endif  // SPCTSTORMOUTLOOKS_H
