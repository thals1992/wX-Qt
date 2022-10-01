// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RADARMOSAICNWS_H
#define RADARMOSAICNWS_H

#include <memory>
#include "objects/ObjectAnimate.h"
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/Photo.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class RadarMosaicNws : public Window {
public:
    explicit RadarMosaicNws(QWidget *);

protected:
    void closeEvent(QCloseEvent *) override;

private:
    void reload();
    void changeSector();
    VBox box;
    HBox boxH;
    Photo photo;
    ComboBox comboboxSector;
    ButtonToggle animateButton;
    ObjectAnimate objectAnimate;
    Shortcut shortcutAnimate;
};

#endif  // RADARMOSAICNWS_H
