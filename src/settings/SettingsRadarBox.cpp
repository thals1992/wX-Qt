// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/SettingsRadarBox.h"
#include "common/GlobalVariables.h"
#include "misc/TextViewerStatic.h"
#include "radarcolorpalette/ObjectColorPalette.h"
#include "objects/ObjectPolygonWarning.h"
#include "util/UtilityList.h"
#include "util/Utility.h"
#include "ui/ObjectSwitch.h"
#include "ui/ObjectDividerLine.h"

SettingsRadarBox::SettingsRadarBox(QWidget * parent) : Widget(parent) {
    box = VBox(this);
    hbox = HBox(this);
    hbox0 = HBox(this);
    hboxBottom = HBox(this);

    vbox0 = VBox(this);
    vbox1 = VBox(this);
    vbox2 = VBox(this);

    button = Button(this, "Keyboard Shortcuts");
    button.connect([this] { launchShortcuts(); });
    hbox0.addWidget(button.get());
    hbox.addLayout(hbox0.get());

    text1 = Text(this, "Reflectivity Palette:");
    comboBoxRefPal = ComboBox(this, refPalChoices);
    comboBoxRefPal.setIndex(UtilityList::findex(Utility::readPref("RADAR_COLOR_PALETTE_94", "CODENH"), refPalChoices));
    comboBoxRefPal.connect([this] { changeRefPal(); });
    hbox1 = HBox(this);
    hbox1.setSpacing(10);
    hbox1.addWidget(text1.get());
    hbox1.addWidget(comboBoxRefPal.get());
    hbox.addLayout(hbox1.get());

    text2 = Text(this, "Velocity Palette:");
    comboBoxVelPal = ComboBox(this, velPalChoices);
    comboBoxVelPal.setIndex(UtilityList::findex(Utility::readPref("RADAR_COLOR_PALETTE_99", "CODENH"), velPalChoices));
    comboBoxVelPal.connect([this] { changeVelPal(); });
    hbox2 = HBox(this);
    hbox2.addWidget(text2.get());
    hbox2.addWidget(comboBoxVelPal.get());
    hbox.addLayout(hbox2.get());

    box.addLayout(hbox.get());
    box.addWidget(ObjectDividerLine(this).get());
    hboxBottom.addLayout(vbox0.get());
    hboxBottom.addLayout(vbox1.get());
    hboxBottom.addLayout(vbox2.get());
    box.addLayout(hboxBottom.get());

    QVector<ObjectSwitch *> alertConfigs = {
        new ObjectSwitch(this, "Canada Borders", "RADARCANADALINES", false),
        new ObjectSwitch(this, "Colormap Legend", "RADAR_COLOR_LEGEND", false),
        new ObjectSwitch(this, "Controls", "RADAR_SHOW_CONTROLS", true),
        new ObjectSwitch(this, "County Lines", "RADAR_SHOW_COUNTY", true),
        new ObjectSwitch(this, "County Labels", "RADAR_COUNTY_LABELS", false),
        new ObjectSwitch(this, "Cities", "COD_CITIES_DEFAULT", false),
        new ObjectSwitch(this, "Hail Indicators", "RADAR_SHOW_HI", false),
        new ObjectSwitch(this, "Highways", "COD_HW_DEFAULT", false),
        new ObjectSwitch(this, "Location Markers", "COD_LOCDOT_DEFAULT", true),
        new ObjectSwitch(this, "Mexico Borders", "RADARMEXICOLINES", false),
        new ObjectSwitch(this, "Multi-pane: share position && radar site", "DUALPANE_SHARE_POSN", true),
        new ObjectSwitch(this, "Observations", "WXOGL_OBS", false),
        new ObjectSwitch(this, "Remember location, site, and product", "WXOGL_REMEMBER_LOCATION", true),
        new ObjectSwitch(this, "Rivers", "COD_LAKES_DEFAULT", false),
        new ObjectSwitch(this, "Secondary Roads", "RADAR_HW_ENH_EXT", false),
        new ObjectSwitch(this, "SPC Convective Outlooks", "RADAR_SHOW_SWO", false),
        new ObjectSwitch(this, "SPC MCD", "RADAR_SHOW_MCD", false),
        new ObjectSwitch(this, "Status Bar", "RADAR_SHOW_STATUSBAR", true),
        new ObjectSwitch(this, "Storm Tracks", "RADAR_SHOW_STI", false),
        new ObjectSwitch(this, "Tornado Vortex Signature", "RADAR_SHOW_TVS", false),
        new ObjectSwitch(this, "Watches", "RADAR_SHOW_WATCH", false),
        new ObjectSwitch(this, "Wind Barbs", "WXOGL_OBS_WINDBARBS", false),
        new ObjectSwitch(this, "WPC Fronts", "RADAR_SHOW_WPC_FRONTS", false),
        new ObjectSwitch(this, "WPC MPD", "RADAR_SHOW_MPD", false),
    };

    numberPickers = {
        new ObjectNumberPicker(this, "Nexrad auto update refresh interval (in minutes)", "RADAR_DATA_REFRESH_INTERVAL", 5, 1, 60, 1),
        new ObjectNumberPicker(this, "Radar Text Size", "RADAR_TEXT_SIZE", 8, 2, 24, 1),
        new ObjectNumberPicker(this, "Wind barbs line size", "RADAR_WB_LINESIZE", 10, 1, 100, 1),
        new ObjectNumberPicker(this, "Storm tracks line size", "RADAR_STI_LINESIZE", 10, 1, 100, 1),
        new ObjectNumberPicker(this, "Convective outlook line size", "RADAR_SWO_LINESIZE", 20, 1, 100, 1),
        new ObjectNumberPicker(this, "Warning line size", "RADAR_WARN_LINESIZE", 20, 1, 100, 1),
        new ObjectNumberPicker(this, "MCD/MPD/Watch line size", "RADAR_WATMCD_LINESIZE", 20, 1, 100, 1),
        new ObjectNumberPicker(this, "State line size", "RADAR_STATE_LINESIZE", 10, 1, 100, 1),
        new ObjectNumberPicker(this, "County line size", "RADAR_COUNTY_LINESIZE", 10, 1, 100, 1),
        new ObjectNumberPicker(this, "Highway line size", "RADAR_HW_LINESIZE", 10, 1, 100, 1),
        new ObjectNumberPicker(this, "Secondary road line size", "RADAR_HWEXT_LINESIZE", 10, 1, 100, 1),
        new ObjectNumberPicker(this, "Lake line size", "RADAR_LAKE_LINESIZE", 10, 1, 100, 1),
        new ObjectNumberPicker(this, "Location marker size", "RADAR_LOCDOT_SIZE", 20, 1, 100, 1),
        new ObjectNumberPicker(this, "Aviation dot size", "RADAR_AVIATION_SIZE", 20, 1, 100, 1),
        new ObjectNumberPicker(this, "Hail marker size", "RADAR_HI_SIZE", 10, 1, 100, 1),
        new ObjectNumberPicker(this, "TVS marker size", "RADAR_TVS_SIZE", 10, 1, 100, 1)
    };


    for (auto type1 : ObjectPolygonWarning::polygonList) {
        ObjectPolygonWarning * warning = ObjectPolygonWarning::polygonDataByType[type1];
        ObjectSwitch * sw = new ObjectSwitch(this, warning->name(), warning->prefTokenEnabled(), false);
        vbox0.addWidget(sw->get());
    }
    int i = 0;
    for (auto config : alertConfigs) {
        if (i >= alertConfigs.size() / 2) {
            vbox1.addWidget(config->get());
        } else {
            vbox0.addWidget(config->get());
        }
        i += 1;
    }
    vbox0.addStretch();
    vbox1.addStretch();
    for (auto config : numberPickers) {
        vbox2.addLayout(config->get());
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
    new TextViewerStatic(this, GlobalVariables::nexradShortcuts, 500, 300);
}
