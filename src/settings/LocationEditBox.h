// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef LOCATIONEDITBOX_H
#define LOCATIONEDITBOX_H

#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/Entry.h"
#include "ui/Table.h"
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Widget.h"

class LocationEditBox : public Widget {
public:
    LocationEditBox(QWidget *, ComboBox *);

private:
    void lookupSearchTerm(const QString&);
    void populateLabels(int index);
    void blankOutButtons();
    void textchanged();
    void saveLocation();
    Table table;
    VBox boxResults;
    VBox box;
    QWidget * parent;
    QStringList cities;
    QStringList citiesSelected;
    Entry cityEdit;
    Entry editName;
    Entry editLat;
    Entry editLon;
    Entry editNexrad;
    Button saveButton;
    QVector<Button> buttons;
    ComboBox * combobox;
};

#endif  // LOCATIONEDITBOX_H
