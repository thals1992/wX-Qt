// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/LocationEditBox.h"
#include <vector>
#include "common/GlobalVariables.h"
#include "objects/LatLon.h"
#include "objects/WString.h"
#include "settings/Location.h"
#include "settings/UtilityLocation.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"

LocationEditBox::LocationEditBox(QWidget * parent)
    : Widget{parent}
    , table{ Table{nullptr} }
    , saveButton{ Button{this, None, "Save"} }
    , cityEdit{ Entry{this} }
    , editName{ Entry{this} }
    , editLat{ Entry{this} }
    , editLon{ Entry{this} }
    , editNexrad{ Entry{this} }
    , cities{ UtilityIO::rawFileToStringArray(GlobalVariables::resDir + "cityall.txt") }
{
    cityEdit.connect([this] { lookupSearchTerm(); });
    saveButton.connect([this] { saveLocation(); });

    table.addRow("Enter City:", cityEdit);
    table.addRow("Name", editName);
    table.addRow("Latitude", editLat);
    table.addRow("Longitude", editLon);
    table.addRow("Nexrad", editNexrad);
    table.addRow("", saveButton);
    box.addLayout(table);

    for (auto index : range(6)) {
        buttons.emplace_back(this, None, "");
        boxResults.addWidget(buttons[index]);
        buttons[index].connect([this, index] { populateLabels(index); });
    }
    boxResults.addStretch();
    box.addLayout(boxResults);
    setLayout(box.getView());
    blankOutButtons();
}

void LocationEditBox::lookupSearchTerm() {
    const auto text = cityEdit.getText();
    editLat.setText(text);
    if (text.size() > 2) {
        vector<string> citiesSelected;
        for (auto& city : cities) {
            if (WString::startsWith(WString::toLower(city), text)) {
                const auto tokens = WString::split(city, ",");
                const auto latLon = LatLon{tokens[1], tokens[2]};
                const auto radar = UtilityLocation::getNearestRadarSites(latLon, 1, false)[0].name;
                citiesSelected.push_back(city + " Radar: " + radar);
            }
        }
        for (size_t index : range(buttons.size())) {
            if (index < citiesSelected.size()) {
                buttons[index].setText(citiesSelected[index]);
                buttons[index].setVisible(true);
            }
            if (index == 0) {
                populateLabels(index);
            }
        }
    } else {
        blankOutButtons();
    }
}

void LocationEditBox::populateLabels(int index) {
    const auto city = buttons[index].getText();
    const auto tokens = WString::split(city, ",");
    const auto latLon = LatLon{tokens[1], tokens[2]};
    const auto radar = UtilityLocation::getNearestRadarSites(latLon, 1, false)[0].name;
    editName.setText(tokens[0]);
    editLat.setText(tokens[1]);
    editLon.setText(tokens[2]);
    editNexrad.setText(radar);
}

void LocationEditBox::blankOutButtons() {
    editName.setText("");
    editLat.setText("");
    editLon.setText("");
    editNexrad.setText("");
    for (auto index : range(buttons.size())) {
        buttons[index].setText("");
        buttons[index].setVisible(false);
    }
}

void LocationEditBox::saveLocation() {
    const auto latLon = LatLon{editLat.getText(), editLon.getText()};
    const auto nameToSave = editName.getText();
    Location::save(latLon, nameToSave);
    Location::setMainScreenComboBox();
    blankOutButtons();
    cityEdit.setText("");
}
