// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RADARMOSAICAWC_H
#define RADARMOSAICAWC_H

#include "objects/ObjectAnimate.h"
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/Photo.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class RadarMosaicAwc  : public Window {
public:
    explicit RadarMosaicAwc(QWidget *);

protected:
    void closeEvent(QCloseEvent *) override;

private:
    void reload();
    void changeProduct();
    void changeSector();
    ObjectAnimate * objectAnimate;
    VBox box;
    HBox boxH;
    ComboBox comboboxProduct;
    ComboBox comboboxSector;
    ButtonToggle animateButton;
    Photo photo;
    Shortcut shortcutAnimate;
};

#endif  // RADARMOSAICAWC_H
