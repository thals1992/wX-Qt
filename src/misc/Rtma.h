// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RTMA_H
#define RTMA_H

#include <string>
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/Photo.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::string;

class Rtma : public Window {
public:
    explicit Rtma(QWidget *);

private:
    void reload();
    void changeProduct();
    void changeSector();
    void changeTime();
    const string prefToken{"RMTA_PROD_INDEX"};
    const string prefTokenSector{"RMTA_SECTOR_INDEX"};
    Photo photo;
    ComboBox comboboxProduct;
    ComboBox comboboxSector;
    ComboBox comboboxTimes;
    int indexProduct{0};
    VBox box;
    HBox hbox;
};

#endif  // RTMA_H
