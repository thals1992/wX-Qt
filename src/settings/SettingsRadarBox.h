// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SETTINGSRADARBOX_H
#define SETTINGSRADARBOX_H

#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/VBox.h"
#include "ui/HBox.h"
#include "ui/ObjectNumberPicker.h"
#include "ui/Text.h"
#include "ui/Widget.h"

class SettingsRadarBox : public Widget {
public:
    SettingsRadarBox(QWidget * parent);

private:
    void changeRefPal();
    void changeVelPal();
    void launchShortcuts();
    VBox box;
    VBox vbox0;
    VBox vbox1;
    VBox vbox2;
    HBox hbox;
    HBox hbox0;
    HBox hbox1;
    HBox hbox2;
    HBox hboxBottom;
    Button button;
    Text text1;
    Text text2;
    QVector<ObjectNumberPicker *> numberPickers;
    ComboBox comboBoxRefPal;
    ComboBox comboBoxVelPal;
    const QStringList refPalChoices = {"CODENH", "DKenh", "NSSL", "NWSD", "GREEN", "AF", "EAK", "NWS"};
    const QStringList velPalChoices = {"CODENH", "EAK", "AF"};
};

#endif  // SETTINGSRADARBOX_H
