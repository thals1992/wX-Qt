// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/SettingsLocationsBox.h"
#include "settings/Location.h"
#include "util/UtilityList.h"

SettingsLocationsBox::SettingsLocationsBox(QWidget * parent): Widget{parent} {
    addLocations();
    setLayout(box.getView());
}

void SettingsLocationsBox::refresh() {
    box.removeChildren();
    Location::refreshLocationData();
    addLocations();
    Location::setMainScreenComboBox();
}

void SettingsLocationsBox::addLocations() {
    buttons.clear();
    locationCards.clear();
    hboxList.clear();
    for (auto index : range(Location::getNumLocations())) {
        hboxList.emplace_back();

        buttons.emplace_back(this, Down, "Move down");
        buttons.back().connect([this, index] () { moveDownClicked(index); });
        hboxList.back().addWidget(buttons.back());

        buttons.emplace_back(this, Up, "Move up");
        buttons.back().connect([this, index] () { moveUpClicked(index); });
        hboxList.back().addWidget(buttons.back());

        buttons.emplace_back(this, Delete, "Delete");
        buttons.back().connect([this, index] { deleteClicked(index); });
        hboxList.back().addWidget(buttons.back());

        locationCards.emplace_back(this, index);
        hboxList.back().addLayout(locationCards.back());
        box.addLayout(hboxList.back());
    }
    box.addStretch();
}

void SettingsLocationsBox::deleteClicked(int locationIndex) {
    Location::deleteItem(locationIndex);
    refresh();
}

void SettingsLocationsBox::moveDownClicked(int position) {
    if (position < (Location::getNumLocations() - 1)) {
        auto locA = ObjectLocation{position};
        auto locB = ObjectLocation{position + 1};
        locA.saveToNewSlot(position + 1);
        locB.saveToNewSlot(position);
    } else {
        auto locA = ObjectLocation{position};
        auto locB = ObjectLocation{0};
        locA.saveToNewSlot(0);
        locB.saveToNewSlot(position);
    }
    refresh();
}

void SettingsLocationsBox::moveUpClicked(int position) {
    if (position > 0) {
        auto locA = ObjectLocation{position - 1};
        auto locB = ObjectLocation{position};
        locA.saveToNewSlot(position);
        locB.saveToNewSlot(position - 1);
    } else {
        auto locA = ObjectLocation{Location::getNumLocations() - 1};
        auto locB = ObjectLocation{0};
        locA.saveToNewSlot(0);
        locB.saveToNewSlot(Location::getNumLocations() - 1);
    }
    refresh();
}
