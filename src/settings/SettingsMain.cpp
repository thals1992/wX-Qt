// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/SettingsMain.h"
#include "common/GlobalVariables.h"
#include "util/Utility.h"

SettingsMain::SettingsMain(QWidget * parent, ComboBox * comboBox, std::function<void()> reloadFn, bool showLocationItems) : Window(parent) {
    this->comboBox = comboBox;
    this->reloadFn = reloadFn;
    setTitle("Settings");
    setSize(600, 600);

    settingsString = getSettings();

    settingsBox = new SettingsBox(parent, comboBox, reloadFn);
    settingsRadarBox = new SettingsRadarBox(parent);
    settingsColorsBox = new SettingsColorsBox(parent);
    if (showLocationItems) {
        settingsLocationsBox = new SettingsLocationsBox(parent, comboBox);
        locationEditBox = new LocationEditBox(parent, comboBox);
        qScrollArea = new QScrollArea();
        qScrollArea->setWidget(settingsLocationsBox);
    }
    aboutBox = new TextViewerStaticBox(this, GlobalVariables::aboutString);
    shortcutsBox = new TextViewerStaticBox(this, GlobalVariables::mainScreenShortcuts);

    tabWidget = TabWidget(this);
    tabWidget.addTab(settingsBox, "General");
    tabWidget.addTab(settingsRadarBox, "Radar");
    tabWidget.addTab(settingsColorsBox, "Colors");
    if (showLocationItems) {
        tabWidget.addTab(qScrollArea, "Locations");
        tabWidget.addTab(locationEditBox, "Add Location");
    }
    tabWidget.addTab(aboutBox, "About " + GlobalVariables::appName);
    tabWidget.addTab(shortcutsBox, "Keyboard Shortcuts");

    if (showLocationItems) {
        tabWidget.connect([this] (int i) {
            if (i == 3) {
                settingsLocationsBox->refresh();
            }
        });
    } else {
        tabWidget.setIndex(1);
    }
    box = VBox(this);
    box.addWidget(tabWidget.get());
    box.getAndShow(this);
}

void SettingsMain::closeEvent([[maybe_unused]] QCloseEvent * event) {
    QString newSettings = getSettings();
    if (newSettings != settingsString) {
        reloadFn();
    }
}

QString SettingsMain::getSettings() {
    QString s;
    auto keys = Utility::prefGetAllKeys();
    for (const auto& key : keys) {
        s += key + ":" + Utility::readPref(key, "");
    }
    return s;
}
