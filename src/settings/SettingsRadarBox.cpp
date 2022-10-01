// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/SettingsRadarBox.h"
#include "common/GlobalVariables.h"
#include "misc/TextViewerStatic.h"
#include "objects/ObjectPolygonWarning.h"
#include "radarcolorpalette/ObjectColorPalette.h"
#include "ui/ObjectDividerLine.h"
#include "util/Utility.h"
#include "util/UtilityList.h"

SettingsRadarBox::SettingsRadarBox(QWidget * parent)
    : Widget{parent}
    , button{ Button{this, None, "Keyboard Shortcuts"} }
    , text1{ Text{this, "Reflectivity Palette:"} }
    , text2{ Text{this, "Velocity Palette:"} }
    , comboBoxRefPal{ ComboBox{this, refPalChoices} }
    , comboBoxVelPal{ ComboBox{this, velPalChoices} }
{
    button.connect([this] { launchShortcuts(); });
    hbox0.addWidget(button.get());
    hbox.addLayout(hbox0.get());

    comboBoxRefPal.setIndex(findex(Utility::readPref("RADAR_COLOR_PALETTE_94", "CODENH"), refPalChoices));
    comboBoxRefPal.connect([this] { changeRefPal(); });
    hbox1.setSpacing(10);
    hbox1.addWidget(text1.get());
    hbox1.addWidget(comboBoxRefPal.get());
    hbox.addLayout(hbox1.get());

    comboBoxVelPal.setIndex(findex(Utility::readPref("RADAR_COLOR_PALETTE_99", "CODENH"), velPalChoices));
    comboBoxVelPal.connect([this] { changeVelPal(); });
    hbox2.addWidget(text2.get());
    hbox2.addWidget(comboBoxVelPal.get());
    hbox.addLayout(hbox2.get());
    box.addLayout(hbox.get());
    box.addWidget(ObjectDividerLine(this).get());
    hboxBottom.addLayout(vbox0.get());
    hboxBottom.addLayout(vbox1.get());
    hboxBottom.addLayout(vbox2.get());
    box.addLayout(hboxBottom.get());

    for (auto type1 : ObjectPolygonWarning::polygonList) {
        auto warning = ObjectPolygonWarning::polygonDataByType[type1].get();
        alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, warning->name(), warning->prefTokenEnabled(), false));
    }
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Canada Borders", "RADARCANADALINES", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Colormap Legend", "RADAR_COLOR_LEGEND", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Controls", "RADAR_SHOW_CONTROLS", true));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "County Lines", "RADAR_SHOW_COUNTY", true));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "County Labels", "RADAR_COUNTY_LABELS", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Cities", "COD_CITIES_DEFAULT", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Hail Indicators", "RADAR_SHOW_HI", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Highways", "COD_HW_DEFAULT", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Location Markers", "COD_LOCDOT_DEFAULT", true));
    // alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Location marker follows GPS", "LOCDOT_FOLLOWS_GPS", false},
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Mexico Borders", "RADARMEXICOLINES", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Multi-pane: share position && radar site", "DUALPANE_SHARE_POSN", true));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Observations", "WXOGL_OBS", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Remember location, site, and product", "WXOGL_REMEMBER_LOCATION", true));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Rivers", "COD_LAKES_DEFAULT", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Secondary Roads", "RADAR_HW_ENH_EXT", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "SPC Convective Outlooks", "RADAR_SHOW_SWO", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "SPC MCD", "RADAR_SHOW_MCD", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Status Bar", "RADAR_SHOW_STATUSBAR", true));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Storm Tracks", "RADAR_SHOW_STI", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Tornado Vortex Signature", "RADAR_SHOW_TVS", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Watches", "RADAR_SHOW_WATCH", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "Wind Barbs", "WXOGL_OBS_WINDBARBS", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "WPC Fronts", "RADAR_SHOW_WPC_FRONTS", false));
    alertConfigs.push_back(std::make_unique<ObjectSwitch>(this, "WPC MPD", "RADAR_SHOW_MPD", false));

    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "Nexrad refresh interval (min)", "RADAR_DATA_REFRESH_INTERVAL", 5, 1, 60, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "Radar Text Size", "RADAR_TEXT_SIZE", 8, 2, 24, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "Wind barbs line size", "RADAR_WB_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "Storm tracks line size", "RADAR_STI_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "Convective outlook line size", "RADAR_SWO_LINESIZE", 20, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "Warning line size", "RADAR_WARN_LINESIZE", 20, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "MCD/MPD/Watch line size", "RADAR_WATMCD_LINESIZE", 20, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "State line size", "RADAR_STATE_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "County line size", "RADAR_COUNTY_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "Highway line size", "RADAR_HW_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "Secondary road line size", "RADAR_HWEXT_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "Lake line size", "RADAR_LAKE_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "Location marker size", "RADAR_LOCDOT_SIZE", 20, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "Aviation dot size", "RADAR_AVIATION_SIZE", 20, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "Hail marker size", "RADAR_HI_SIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<ObjectNumberPicker>(this, "TVS marker size", "RADAR_TVS_SIZE", 10, 1, 100, 1));

    for (size_t i : range(alertConfigs.size())) {
        if (i >= alertConfigs.size() / 2) {
            vbox1.addWidget(alertConfigs[i]->get());
        } else {
            vbox0.addWidget(alertConfigs[i]->get());
        }
    }
    vbox0.addStretch();
    vbox1.addStretch();
    for (auto i : range(numberPickers.size())) {
        vbox2.addLayout(numberPickers[i]->get());
    }
    vbox2.addStretch();
    setLayout(box.get());
}

void SettingsRadarBox::changeRefPal() {
    Utility::writePref("RADAR_COLOR_PALETTE_94", comboBoxRefPal.getValue());
    ObjectColorPalette::loadColorMap(94);
}

void SettingsRadarBox::changeVelPal() {
    Utility::writePref("RADAR_COLOR_PALETTE_99", comboBoxVelPal.getValue());
    ObjectColorPalette::loadColorMap(99);
}

void SettingsRadarBox::launchShortcuts() {
    new TextViewerStatic{this, GlobalVariables::nexradShortcuts, 500, 500};
}
