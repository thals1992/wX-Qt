// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/LocationEditBox.h"
#include "common/GlobalVariables.h"
#include "objects/LatLon.h"
#include "settings/Location.h"
#include "settings/UtilityLocation.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"

LocationEditBox::LocationEditBox(QWidget * parent, ComboBox * locationChooserMainScreen): Widget(parent) {
    this->parent = parent;
    combobox = locationChooserMainScreen;
    cities = UtilityIO::rawFileToStringArray(GlobalVariables::resDir + "cityall.txt");
    boxResults = VBox(nullptr);
    box = VBox(nullptr);

    cityEdit = Entry(this);
    cityEdit.connect([this] { textchanged(); });

    saveButton = Button(this, "Save");
    saveButton.connect([this] { saveLocation(); });

    table = Table(nullptr);
    editName = Entry(this);
    editLat = Entry(this);
    editLon = Entry(this);
    editNexrad = Entry(this);

    table.addRow("Enter City:", cityEdit.get());
    table.addRow("Name", editName.get());
    table.addRow("Latitude", editLat.get());
    table.addRow("Longitude", editLon.get());
    table.addRow("Nexrad", editNexrad.get());
    table.addRow("", saveButton.get());
    box.addLayout(table.get());

    for (auto index : UtilityList::range(6)) {
        auto button = Button(this, "");
        buttons.push_back(button);
        boxResults.addWidget(buttons[index].get());
        buttons[index].connect([this, index] { populateLabels(index); });
    }
    boxResults.addStretch();
    box.addLayout(boxResults.get());
    setLayout(box.get());
    blankOutButtons();
}

void LocationEditBox::textchanged() {
    auto text = cityEdit.getText();
    editLat.setText(text);
    lookupSearchTerm(text);
}

void LocationEditBox::lookupSearchTerm(const QString& text) {
    if (text.size() > 2) {
        QStringList citiesSelected;
        for (auto city : cities) {
            if (city.toLower().startsWith(text)) {
                auto tokens = city.split(",");
                auto latLon = LatLon(tokens[1], tokens[2]);
                auto radar = UtilityLocation::getNearestRadarSites(latLon, 1, false)[0].name;
                citiesSelected.push_back(city + " Radar: " + radar);
            }
        }
        for (auto index : UtilityList::range(buttons.size())) {
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
    auto city = buttons[index].getText();
    auto tokens = city.split(",");
    auto latLon = LatLon(tokens[1], tokens[2]);
    auto radar = UtilityLocation::getNearestRadarSites(latLon, 1, false)[0].name;
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
    for (auto index : UtilityList::range(buttons.size())) {
        buttons[index].setText("");
        buttons[index].setVisible(false);
    }
}

void LocationEditBox::saveLocation() {
    auto latLon = LatLon(editLat.getText(), editLon.getText());
    auto nameToSave = editName.getText();
    Location::save(latLon, nameToSave);
    combobox->appendText(editName.getText());
    blankOutButtons();
    cityEdit.setText("");
}
