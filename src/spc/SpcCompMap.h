// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCCOMPMAP_H
#define SPCCOMPMAP_H

#include <string>
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/Photo.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::string;

class SpcCompMap : public Window {
public:
    explicit SpcCompMap(QWidget *);

private:
    void reload();
    void changeProduct();
    const string prefToken{"SPCCOMPMAP_LAYERSTRIOS"};
    Photo photo;
    ComboBox comboboxProduct;
    VBox box;
    HBox buttonBox;
    Button buttonBack;
    Button buttonForward;
    string product;
    int index;
};

#endif  // SPCCOMPMAP_H
