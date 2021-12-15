// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SETTINGSLOCATIONSBOX_H
#define SETTINGSLOCATIONSBOX_H

#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/ObjectCardLocationItem.h"
#include "ui/Widget.h"

class SettingsLocationsBox : public Widget {
public:
    explicit SettingsLocationsBox(QWidget *, ComboBox *);
    void refresh();

private:
    void refreshCombobox();
    void addLocations();
    void deleteClicked(int);
    void moveDownClicked(int);
    void moveUpClicked(int);
    QWidget * parent;
    QVector<Button> buttons;
    QVector<ObjectCardLocationItem> locationCards;
    QVector<HBox> hboxList;
    VBox box;
    ComboBox * combobox;
};

#endif  // SETTINGSLOCATIONSBOX_H
