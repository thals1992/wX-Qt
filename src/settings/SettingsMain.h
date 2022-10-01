// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SETTINGSMAIN_H
#define SETTINGSMAIN_H

#include <functional>
#include <string>
#include "settings/LocationEditBox.h"
#include "settings/SettingsBox.h"
#include "settings/SettingsColorsBox.h"
#include "settings/SettingsLocationsBox.h"
#include "settings/SettingsRadarBox.h"
#include "ui/ComboBox.h"
#include "ui/ScrolledWindow.h"
#include "ui/Shortcut.h"
#include "ui/TabWidget.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::function;
using std::string;

class SettingsMain : public Window {
public:
    SettingsMain(QWidget *, const function<void()>&, bool, bool);

protected:
    void closeEvent(QCloseEvent *) override;

private:
    static string getSettings();
    std::function<void()> reloadFn;
    VBox box;
    ScrolledWindow sw;
    LocationEditBox * locationEditBox;
    SettingsBox * settingsBox;
    SettingsRadarBox * settingsRadarBox;
    SettingsColorsBox * settingsColorsBox;
    SettingsLocationsBox * settingsLocationsBox;
    TabWidget tabWidget;
    string settingsString;
    Shortcut shortcutGeneral;
    Shortcut shortcutRadar;
    Shortcut shortcutColors;
    Shortcut shortcutLocations;
    Shortcut shortcutAddLocation;
};

#endif  // SETTINGSMAIN_H
