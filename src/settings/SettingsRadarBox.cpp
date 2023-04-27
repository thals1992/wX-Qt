// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/SettingsRadarBox.h"
#include "common/GlobalVariables.h"
#include "misc/TextViewerStatic.h"
#include "objects/PolygonWarning.h"
#include "radarcolorpalette/ColorPalette.h"
#include "ui/DividerLine.h"
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
    hbox0.addWidget(button);
    hbox.addLayout(hbox0);

    comboBoxRefPal.setIndex(findex(Utility::readPref("RADAR_COLOR_PALETTE_94", "CODENH"), refPalChoices));
    comboBoxRefPal.connect([this] { changeRefPal(); });
    hbox1.setSpacing(10);
    hbox1.addWidget(text1);
    hbox1.addWidget(comboBoxRefPal);
    hbox.addLayout(hbox1);

    comboBoxVelPal.setIndex(findex(Utility::readPref("RADAR_COLOR_PALETTE_99", "CODENH"), velPalChoices));
    comboBoxVelPal.connect([this] { changeVelPal(); });
    hbox2.addWidget(text2);
    hbox2.addWidget(comboBoxVelPal);
    hbox.addLayout(hbox2);
    box.addLayout(hbox);
    box.addWidget(DividerLine(this).get());
    hboxBottom.addLayout(vbox0);
    hboxBottom.addLayout(vbox1);
    hboxBottom.addLayout(vbox2);
    box.addLayout(hboxBottom);

    for (auto type1 : PolygonWarning::polygonList) {
        auto warning = PolygonWarning::byType[type1].get();
        alertConfigs.push_back(std::make_unique<Switch>(this, warning->name(), warning->prefTokenEnabled(), false));
    }
    alertConfigs.push_back(std::make_unique<Switch>(this, "Canada Borders", "RADARCANADALINES", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Colormap Legend", "RADAR_COLOR_LEGEND", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Controls", "RADAR_SHOW_CONTROLS", true));
    alertConfigs.push_back(std::make_unique<Switch>(this, "County Lines", "RADAR_SHOW_COUNTY", true));
    alertConfigs.push_back(std::make_unique<Switch>(this, "County Labels", "RADAR_COUNTY_LABELS", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Cities", "COD_CITIES_DEFAULT", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Hail Indicators", "RADAR_SHOW_HI", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Highways", "COD_HW_DEFAULT", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Location Markers", "COD_LOCDOT_DEFAULT", true));
    // alertConfigs.push_back(std::make_unique<Switch>(this, "Location marker follows GPS", "LOCDOT_FOLLOWS_GPS", false},
    alertConfigs.push_back(std::make_unique<Switch>(this, "Mexico Borders", "RADARMEXICOLINES", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Multi-pane: share position && radar site", "DUALPANE_SHARE_POSN", true));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Observations", "WXOGL_OBS", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Remember location, site, and product", "WXOGL_REMEMBER_LOCATION", true));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Rivers", "COD_LAKES_DEFAULT", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Secondary Roads", "RADAR_HW_ENH_EXT", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "SPC Convective Outlooks", "RADAR_SHOW_SWO", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "SPC MCD", "RADAR_SHOW_MCD", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Status Bar", "RADAR_SHOW_STATUSBAR", true));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Storm Tracks", "RADAR_SHOW_STI", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Tornado Vortex Signature", "RADAR_SHOW_TVS", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Watches", "RADAR_SHOW_WATCH", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "Wind Barbs", "WXOGL_OBS_WINDBARBS", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "WPC Fronts", "RADAR_SHOW_WPC_FRONTS", false));
    alertConfigs.push_back(std::make_unique<Switch>(this, "WPC MPD", "RADAR_SHOW_MPD", false));

    numberPickers.push_back(std::make_unique<NumberPicker>(this, "Nexrad refresh interval (min)", "RADAR_DATA_REFRESH_INTERVAL", 5, 1, 60, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "Radar Text Size", "RADAR_TEXT_SIZE", 8, 2, 24, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "Wind barbs line size", "RADAR_WB_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "Storm tracks line size", "RADAR_STI_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "Convective outlook line size", "RADAR_SWO_LINESIZE", 20, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "Warning line size", "RADAR_WARN_LINESIZE", 20, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "MCD/MPD/Watch line size", "RADAR_WATMCD_LINESIZE", 20, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "State line size", "RADAR_STATE_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "County line size", "RADAR_COUNTY_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "Highway line size", "RADAR_HW_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "Secondary road line size", "RADAR_HWEXT_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "Lake line size", "RADAR_LAKE_LINESIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "Location marker size", "RADAR_LOCDOT_SIZE", 20, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "Aviation dot size", "RADAR_AVIATION_SIZE", 20, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "Hail marker size", "RADAR_HI_SIZE", 10, 1, 100, 1));
    numberPickers.push_back(std::make_unique<NumberPicker>(this, "TVS marker size", "RADAR_TVS_SIZE", 10, 1, 100, 1));

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
    setLayout(box.getView());
}

void SettingsRadarBox::changeRefPal() {
    Utility::writePref("RADAR_COLOR_PALETTE_94", comboBoxRefPal.getValue());
    ColorPalette::loadColorMap(94);
}

void SettingsRadarBox::changeVelPal() {
    Utility::writePref("RADAR_COLOR_PALETTE_99", comboBoxVelPal.getValue());
    ColorPalette::loadColorMap(99);
}

void SettingsRadarBox::launchShortcuts() {
    new TextViewerStatic{this, GlobalVariables::nexradShortcuts, 500, 500};
}
