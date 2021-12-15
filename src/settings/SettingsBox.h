// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SETTINGSBOX_H
#define SETTINGSBOX_H

#include <functional>
#include "ui/ComboBox.h"
#include "ui/ObjectSwitch.h"
#include "ui/ObjectNumberPicker.h"
#include "ui/ScrolledWindow.h"
#include "ui/Shortcut.h"
#include "ui/Text.h"
#include "ui/Widget.h"
#include "ui/VBox.h"
#include "ui/HBox.h"

class SettingsBox : public Widget {
public:
    SettingsBox(QWidget * parent, ComboBox * comboBox, std::function<void()>);

private:
    ComboBox * comboBox;
    std::function<void()> reloadFn;
    ObjectSwitch * sw1;
    ObjectSwitch * sw2;
    ObjectSwitch * sw3;
    ObjectNumberPicker * np1;
    ObjectNumberPicker * np2;
    ScrolledWindow sw;
    VBox box;
    HBox hbox0;
    Shortcut shortcutAddLoction;
    Shortcut shortcutManageLocations;
    Shortcut shortcutColor;
    Shortcut shortcutRadar;
    Text homeScreenLabel;
    Text generalLabel;
};

#endif  // SETTINGSBOX_H
