// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SETTINGSCOLORSBOX_H
#define SETTINGSCOLORSBOX_H

#include "objects/WXColor.h"
#include "ui/HBox.h"
#include "ui/ObjectColorLabel.h"
#include "ui/VBox.h"
#include "ui/Widget.h"

class SettingsColorsBox : public Widget {
public:
    explicit SettingsColorsBox(QWidget *);

private:
    void loadColors();
    HBox box;
    VBox vbox1;
    VBox vbox2;
    QVector<WXColor> colors;
    QVector<ObjectColorLabel *> objectColorLabels;
};

#endif  // SETTINGSCOLORSBOX_H
