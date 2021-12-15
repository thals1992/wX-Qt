// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "settings/SettingsLocationsBox.h"
#include "settings/Location.h"
#include "ui/Icon.h"
#include "util/UtilityList.h"

SettingsLocationsBox::SettingsLocationsBox(QWidget * parent, ComboBox * combobox): Widget(parent) {
    this->parent = parent;
    this->combobox = combobox;
    addLocations();
    setLayout(box.get());
}

void SettingsLocationsBox::refresh() {
    box.removeChildren();
    Location::refreshLocationData();
    addLocations();
}

void SettingsLocationsBox::refreshCombobox() {
    combobox->block();
    combobox->removeAll();
    for (auto index : UtilityList::range(Location::getNumLocations())) {
        combobox->appendText(Location::getName(index));
    }
    combobox->setIndex(Location::getCurrentLocation());
    combobox->unblock();
}

void SettingsLocationsBox::addLocations() {
    buttons.clear();
    locationCards.clear();
    hboxList.clear();
    for (auto index : UtilityList::range(Location::getNumLocations())) {
        hboxList.push_back(HBox(this));

        buttons.push_back(Button(this, Icon::Down, "Move down"));
        buttons.back().connect([this, index] () { moveDownClicked(index); });
        hboxList.back().addWidget(buttons.back().get());

        buttons.push_back(Button(this, Icon::Up, "Move up"));
        buttons.back().connect([this, index] () { moveUpClicked(index); });
        hboxList.back().addWidget(buttons.back().get());

        buttons.push_back(Button(this, Icon::Delete, "Delete"));
        buttons.back().connect([this, index] { deleteClicked(index); });
        hboxList.back().addWidget(buttons.back().get());

        locationCards.push_back(ObjectCardLocationItem(this, index));
        hboxList.back().addLayout(locationCards.back().get());
        box.addLayout(hboxList.back().get());
    }
    box.addStretch();
}

void SettingsLocationsBox::deleteClicked(int locationIndex) {
    Location::deleteItem(locationIndex);
    refresh();
    refreshCombobox();
}

void SettingsLocationsBox::moveDownClicked(int locationIndex) {
    auto position = locationIndex;
    if (position < (Location::getNumLocations() - 1)) {
        auto locA = ObjectLocation(position);
        auto locB = ObjectLocation(position + 1);
        locA.saveToNewSlot(position + 1);
        locB.saveToNewSlot(position);
    } else {
        auto locA = ObjectLocation(position);
        auto locB = ObjectLocation(0);
        locA.saveToNewSlot(0);
        locB.saveToNewSlot(position);
    }
    refresh();
    refreshCombobox();
}

void SettingsLocationsBox::moveUpClicked(int locationIndex) {
    auto position = locationIndex;
    if (position > 0) {
        auto locA = ObjectLocation(position - 1);
        auto locB = ObjectLocation(position);
        locA.saveToNewSlot(position);
        locB.saveToNewSlot(position - 1);
    } else {
        auto locA = ObjectLocation(Location::getNumLocations() - 1);
        auto locB = ObjectLocation(0);
        locA.saveToNewSlot(0);
        locB.saveToNewSlot(Location::getNumLocations() - 1);
    }
    refresh();
    refreshCombobox();
}
