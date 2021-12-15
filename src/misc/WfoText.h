// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WFOTEXT_H
#define WFOTEXT_H

#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/ScrolledWindow.h"
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class WfoText : public Window {
public:
    explicit WfoText(QWidget *);

private:
    void reload();
    void changeProduct();
    void changeSector();
    Text text;
    QString product = "AFD";
    QString sector = "";
    HBox boxH;
    VBox box;
    ComboBox comboboxProduct;
    ComboBox comboboxSector;
    HBox boxText;
    QVector<Text> textList;
    ScrolledWindow sw;
};

#endif  // WFOTEXT_H
