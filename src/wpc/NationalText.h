// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WPCNATIONALTEXT_H
#define WPCNATIONALTEXT_H

#include <string>
#include <vector>
#include "ui/Button.h"
#include "ui/PopoverMenu.h"
#include "ui/Shortcut.h"
#include "ui/Text.h"
#include "ui/Window.h"
#include "ui/ScrolledWindow.h"
#include "ui/VBox.h"

using std::string;
using std::vector;

class NationalText : public Window {
public:
    NationalText(QWidget *, const string&);

private:
    void reload();
    void changeProductByCode(const string&);
    string product{"PMDSPD"};
    int index{};
    const string prefTokenProduct{"WPCTEXT_PARAM_LAST_USED"};
    VBox box;
    HBox hbox;
    ScrolledWindow sw;
    Text text;
    vector<PopoverMenu> popoverMenus;
    bool savePref{true};
    Button buttonBack;
    Button buttonForward;
};

#endif  // WPCNATIONALTEXT_H
