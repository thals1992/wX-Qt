// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/SettingsMain.h"
#include <string>
#include "util/Utility.h"

using std::string;

SettingsMain::SettingsMain(QWidget * parent, const function<void()>& reloadFn, bool showLocationItems, bool showRadarFirst)
    : Window{parent}
    , reloadFn{ reloadFn }
    , sw{ ScrolledWindow{this, box} }
    , settingsBox{ new SettingsBox{parent} }
    , settingsRadarBox{ new SettingsRadarBox{parent} }
    , settingsColorsBox{ new SettingsColorsBox{parent} }
    , tabWidget{ TabWidget{this} }
    , settingsString{ getSettings() }
    , shortcutGeneral{ Shortcut{QKeySequence{"G"}, this} }
    , shortcutRadar{ Shortcut{QKeySequence{"R"}, this} }
    , shortcutColors{ Shortcut{QKeySequence{"C"}, this} }
    , shortcutLocations{ Shortcut{QKeySequence{"L"}, this} }
    , shortcutAddLocation{ Shortcut{QKeySequence{"A"}, this} }
{
    setTitle("Settings");
//    setSize(800, 600);
    if (showLocationItems) {
        settingsLocationsBox = new SettingsLocationsBox{parent};
        locationEditBox = new LocationEditBox{parent};
    }
    tabWidget.addTab(settingsBox, "General");
    tabWidget.addTab(settingsRadarBox, "Radar");
    tabWidget.addTab(settingsColorsBox, "Colors");
    if (showLocationItems) {
        tabWidget.addTab(settingsLocationsBox, "Locations");
        tabWidget.addTab(locationEditBox, "Add Location");
    }
    if (showRadarFirst) {
        tabWidget.setIndex(1);
    }
    if (showLocationItems) {
        tabWidget.connect([this] (int i) {
            if (i == 3) {
                settingsLocationsBox->refresh();
            }
        });
    } else {
        tabWidget.setIndex(1);
    }
    box.addWidget(tabWidget.get());

    shortcutGeneral.connect([this] { tabWidget.setIndex(0); });
    shortcutRadar.connect([this] { tabWidget.setIndex(1); });
    shortcutColors.connect([this] { tabWidget.setIndex(2); });
    shortcutLocations.connect([this] { tabWidget.setIndex(3); });
    shortcutAddLocation.connect([this] { tabWidget.setIndex(4); });
}

void SettingsMain::closeEvent([[maybe_unused]] QCloseEvent * event) {
    const auto newSettings = getSettings();
    if (newSettings != settingsString) {
        reloadFn();
    }
}

string SettingsMain::getSettings() {
    string s;
    const auto keys = Utility::prefGetAllKeys();
    for (const auto& key : keys) {
        s += key + ":" + Utility::readPref(key, "");
    }
    return s;
}
