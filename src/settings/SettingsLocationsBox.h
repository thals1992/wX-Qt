// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SETTINGSLOCATIONSBOX_H
#define SETTINGSLOCATIONSBOX_H

#include <vector>
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/CardLocationItem.h"
#include "ui/Widget.h"

using std::vector;

class SettingsLocationsBox : public Widget {
public:
    explicit SettingsLocationsBox(QWidget *);
    void refresh();

private:
    void addLocations();
    void deleteClicked(int);
    void moveDownClicked(int);
    void moveUpClicked(int);
    vector<Button> buttons;
    vector<CardLocationItem> locationCards;
    vector<HBox> hboxList;
    VBox box;
};

#endif  // SETTINGSLOCATIONSBOX_H
