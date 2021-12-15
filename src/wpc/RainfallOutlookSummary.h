// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WPCRAINFALLOUTLOOKSUMMARY_H
#define WPCRAINFALLOUTLOOKSUMMARY_H

#include "ui/HBox.h"
#include "ui/Image.h"
#include "ui/Window.h"

class RainfallOutlookSummary : public Window {
public:
    explicit RainfallOutlookSummary(QWidget *);

private:
    void launch(int);
    HBox box;
    QStringList urls;
    QVector<Image> images;
};

#endif  // WPCRAINFALLOUTLOOKSUMMARY_H
