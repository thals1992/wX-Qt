// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef VISGOESVIEWER_H
#define VISGOESVIEWER_H

#include <memory>
#include <string>
#include "objects/ObjectAnimate.h"
#include "ui/ButtonToggle.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::string;

class GoesViewer : public Window {
public:
    GoesViewer(QWidget *, const string& url, const string& product = "", const string& sector = "");

protected:
    void closeEvent(QCloseEvent *) override;

private:
    void reload();
    void changeSector();
    void changeProduct();
    void changeCount();
    HBox boxH;
    VBox box;
    Photo photo;
    ComboBox comboboxSector;
    ComboBox comboboxProduct;
    ComboBox comboboxCount;
    ButtonToggle animateButton;
    ObjectAnimate objectAnimate;
    bool goesFloater{false};
    string goesFloaterUrl;
    Shortcut shortcutAnimate;
};

#endif  // VISGOESVIEWER_H
