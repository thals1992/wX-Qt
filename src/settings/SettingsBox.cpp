// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/SettingsBox.h"
#include "objects/PrefBool.h"
#include "settings/UIPreferences.h"
#include "ui/ObjectDividerLine.h"

SettingsBox::SettingsBox(QWidget * parent, ComboBox * comboBox, std::function<void()> reloadFn) : Widget(parent) {
    this->comboBox = comboBox;
    this->reloadFn = reloadFn;

    box = VBox(this);
    box.setSpacing(10);
    hbox0 = HBox(this);
    box.addLayout(hbox0.get());

    homeScreenLabel = Text(this, "Homescreen widgets:");
    homeScreenLabel.setBlue();
    box.addWidget(homeScreenLabel.get());

    for (const auto& item : UIPreferences::homeScreenItemsImage) {
        auto sw = ObjectSwitch::fromPrefBool(this, item);
        box.addWidget(sw->get());
    }

    for (const auto& item : UIPreferences::homeScreenItemsText) {
        auto sw = ObjectSwitch::fromPrefBool(this, item);
        box.addWidget(sw->get());
    }

    box.addWidget(ObjectDividerLine(this).get());
    generalLabel = Text(this, "General preferences:");
    generalLabel.setBlue();
    box.addWidget(generalLabel.get());

    // sw0 = new ObjectSwitch(this, "Show Nexrad on main screen", "NEXRAD_ON_MAIN_SCREEN", false);
    // box.addWidget(sw0->get());

    sw1 = new ObjectSwitch(this, "Use new NWS API", "USE_NWS_API_SEVEN_DAY", false);
    box.addWidget(sw1->get());

    sw2 = new ObjectSwitch(this, "Use new NWS API - Hourly", "USE_NWS_API_HOURLY", true);
    box.addWidget(sw2->get());

    sw3 = new ObjectSwitch(this, "Show mini SevereDashboard on main screen", "MAINSCREEN_SEVERE_DASH", false);
    box.addWidget(sw3->get());

    np1 = new ObjectNumberPicker(this, "Main screen image size", "MAIN_SCREEN_IMAGE_SIZE", 400, 200, 800, 50);
    box.addLayout(np1->get());

    np2 = new ObjectNumberPicker(this, "Toolbar icon size", "TOOLBAR_ICON_SIZE", 36, 10, 72, 4);
    box.addLayout(np2->get());

    box.addStretch();
    setLayout(box.get());
}
