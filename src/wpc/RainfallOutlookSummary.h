// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WPCRAINFALLOUTLOOKSUMMARY_H
#define WPCRAINFALLOUTLOOKSUMMARY_H

#include <vector>
#include "ui/HBox.h"
#include "ui/Image.h"
#include "ui/Window.h"

using std::vector;

class RainfallOutlookSummary : public Window {
public:
    explicit RainfallOutlookSummary(QWidget *);

private:
    HBox box;
    vector<Image> images;
};

#endif  // WPCRAINFALLOUTLOOKSUMMARY_H
