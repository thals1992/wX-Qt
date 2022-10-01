// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCTSTORMOUTLOOKS_H
#define SPCTSTORMOUTLOOKS_H

#include <vector>
#include "ui/HBox.h"
#include "ui/Window.h"

using std::vector;

class SpcTstormOutlooks : public Window {
public:
    explicit SpcTstormOutlooks(QWidget *);

private:
    HBox box;
    vector<Image> images;
};

#endif  // SPCTSTORMOUTLOOKS_H
