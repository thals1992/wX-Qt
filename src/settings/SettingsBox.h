// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SETTINGSBOX_H
#define SETTINGSBOX_H

#include <functional>
#include <memory>
#include <vector>
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/ObjectSwitch.h"
#include "ui/ObjectNumberPicker.h"
#include "ui/ScrolledWindow.h"
#include "ui/Shortcut.h"
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Widget.h"

using std::vector;

class SettingsBox : public Widget {
public:
    explicit SettingsBox(QWidget *);

private:
    vector<std::unique_ptr<ObjectSwitch>> configs;
    Button button;
    Button buttonAbout;
    VBox box;
    HBox hbox0;
    Text homeScreenLabel;
    Text generalLabel;
    std::unique_ptr<ObjectNumberPicker> np1;
    std::unique_ptr<ObjectNumberPicker> np2;
};

#endif  // SETTINGSBOX_H
