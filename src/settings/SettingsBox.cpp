// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/SettingsBox.h"
#include "common/GlobalVariables.h"
#include "misc/TextViewerStatic.h"
#include "settings/UIPreferences.h"
#include "ui/DividerLine.h"
#include "util/UtilityList.h"

SettingsBox::SettingsBox(QWidget * parent)
    : Widget{parent}
    , button{ Button{this, None, "Keyboard Shortcuts"} }
    , buttonAbout{ Button{this, None, "About " + GlobalVariables::appName} }
    , homeScreenLabel{ Text{this, "Homescreen widgets:"} }
    , generalLabel{ Text{this, "General preferences:"} }
    , np1{ std::make_unique<NumberPicker>(this, "Main screen image size", "MAIN_SCREEN_IMAGE_SIZE", 400, 200, 800, 50) }
    , np2{ std::make_unique<NumberPicker>(this, "Toolbar icon size", "TOOLBAR_ICON_SIZE", 36, 10, 72, 4) }
{
    configs.push_back(std::make_unique<Switch>(this, "Show Nexrad on main screen", "NEXRAD_ON_MAIN_SCREEN", false));
    configs.push_back(std::make_unique<Switch>(this, "Use new NWS API", "USE_NWS_API_SEVEN_DAY", false));
    configs.push_back(std::make_unique<Switch>(this, "Use new NWS API - Hourly", "USE_NWS_API_HOURLY", true));
    configs.push_back(std::make_unique<Switch>(this, "Show mini SevereDashboard on main screen", "MAINSCREEN_SEVERE_DASH", false));
    configs.push_back(std::make_unique<Switch>(this, "Toggle scroll wheel motion", "NEXRAD_SCROLLWHEEL", false));
    configs.push_back(std::make_unique<Switch>(this, "Remember last GOES image", "REMEMBER_GOES", false));
    configs.push_back(std::make_unique<Switch>(this, "Remember last Radar Mosaic image", "REMEMBER_MOSAIC", false));

    box.setSpacing(10);
    box.addLayout(hbox0);

    button.connect([this] { new TextViewerStatic{this, GlobalVariables::mainScreenShortcuts}; });
    hbox0.addWidget(button);

    buttonAbout.connect([this] { new TextViewerStatic{this, GlobalVariables::aboutString}; });
    hbox0.addWidget(buttonAbout);

    homeScreenLabel.setBlue();
    box.addWidget(homeScreenLabel);

    for (const auto& item : UIPreferences::homeScreenItemsImage) {
        auto sw = Switch::fromPrefBool(this, item);
        box.addWidget(sw->get());
    }

    for (const auto& item : UIPreferences::homeScreenItemsText) {
        auto sw = Switch::fromPrefBool(this, item);
        box.addWidget(sw->get());
    }
    box.addWidget(DividerLine(this).get());
    generalLabel.setBlue();
    box.addWidget(generalLabel);

    for (auto i : range(configs.size())) {
        box.addWidget(configs[i]->get());
    }
    box.addLayout(np1->get());
    box.addLayout(np2->get());
    box.addStretch();
    setLayout(box.getView());
}
