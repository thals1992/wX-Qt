// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCFIRESUMMARY_H
#define SPCFIRESUMMARY_H

#include "ui/HBox.h"
#include "ui/Image.h"
#include "ui/Window.h"

class SpcFireSummary  : public Window {
public:
    explicit SpcFireSummary(QWidget *);

private:
    void launch(int);
    HBox box;
    QVector<Image> images;
    QStringList urls;
};

#endif  // SPCFIRESUMMARY_H
