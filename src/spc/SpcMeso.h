// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCMESO_H
#define SPCMESO_H

#include <memory>
#include <string>
#include <vector>
#include <QCloseEvent>
#include "objects/ObjectAnimate.h"
#include "ui/Button.h"
#include "ui/ButtonToggle.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/PopoverMenu.h"
#include "ui/Shortcut.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::string;
using std::vector;

class SpcMeso : public Window {
public:
    explicit SpcMeso(QWidget *);

protected:
    void closeEvent(QCloseEvent *) override;

private:
    void reload();
    void changeProductForFav(int);
    void changeProductByCode(const string& label);
    void changeSector();
    string getUrl() const;
    void moveLeftClicked();
    void moveRightClicked();
    HBox boxH;
    HBox imageLayout;
    VBox boxFav;
    VBox box;
    Photo photo;
    ComboBox comboboxSector;
    Button buttonBack;
    Button buttonForward;
    ButtonToggle animateButton;
    ObjectAnimate objectAnimate;
    const string prefTokenProduct{"SPCMESO1_PARAM_LAST_USED"};
    const string prefTokenSector{"SPCMESO1_SECTOR_LAST_USED"};
    vector<Button> buttons;
    int index{};
    vector<PopoverMenu> popoverMenus;
    Shortcut shortcutAnimate;
    Shortcut shortcutLeft;
    Shortcut shortcutRight;
};

#endif  // SPCMESO_H
