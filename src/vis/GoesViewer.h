// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef VISGOESVIEWER_H
#define VISGOESVIEWER_H

#include "objects/ObjectAnimate.h"
#include "ui/ButtonToggle.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class GoesViewer : public Window {
public:
    GoesViewer(QWidget *, QString url, QString product = "", QString sector = "");

protected:
    void closeEvent(QCloseEvent *) override;

private:
    void reload();
    void changeSector();
    void changeProduct();
    ObjectAnimate * objectAnimate;
    HBox boxH;
    VBox box;
    ButtonToggle animateButton;
    ComboBox comboboxProduct;
    ComboBox comboboxSector;
    Photo photo;
    bool goesFloater = false;
    QString goesFloaterUrl;
    Shortcut shortcutAnimate;
};

#endif  // VISGOESVIEWER_H
