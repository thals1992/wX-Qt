// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCFIRESUMMARY_H
#define SPCFIRESUMMARY_H

#include <string>
#include <vector>
#include "ui/HBox.h"
#include "ui/Image.h"
#include "ui/Window.h"

using std::string;
using std::vector;

class SpcFireSummary  : public Window {
public:
    explicit SpcFireSummary(QWidget *);

private:
    vector<string> urls;
    HBox box;
    vector<Image> images;
};

#endif  // SPCFIRESUMMARY_H
