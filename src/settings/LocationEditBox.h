// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef LOCATIONEDITBOX_H
#define LOCATIONEDITBOX_H

#include <string>
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/Entry.h"
#include "ui/HBox.h"
#include "ui/Table.h"
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Widget.h"

using std::string;

class LocationEditBox : public Widget {
public:
    explicit LocationEditBox(QWidget *);

private:
    void lookupSearchTerm();
    void populateLabels(int);
    void blankOutButtons();
    void saveLocation();
    VBox boxResults;
    HBox box;
    Table table;
    Button saveButton;
    Entry cityEdit;
    Entry editName;
    Entry editLat;
    Entry editLon;
    Entry editNexrad;
    vector<Button> buttons;
    vector<string> cities;
};

#endif  // LOCATIONEDITBOX_H
