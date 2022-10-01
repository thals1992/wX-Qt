// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WPCNATIONALIMAGES_H
#define WPCNATIONALIMAGES_H

#include <string>
#include <vector>
#include "ui/Button.h"
#include "ui/HBox.h"
#include "ui/Photo.h"
#include "ui/PopoverMenu.h"
#include "ui/Shortcut.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::string;
using std::vector;

class NationalImages : public Window {
public:
    explicit NationalImages(QWidget *);

private:
    void reload();
    void changeProductByCode(const string&);
    void moveLeftClicked();
    void moveRightClicked();
    const string prefToken{"WPCIMG_PARAM_LAST_USED"};
    VBox box;
    HBox hbox;
    vector<PopoverMenu> popoverMenus;
    Photo photo;
    Button buttonBack;
    Button buttonForward;
    int index;
    Shortcut shortcutLeft;
    Shortcut shortcutRight;
};

#endif  // WPCNATIONALIMAGES_H
