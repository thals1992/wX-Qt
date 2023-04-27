// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NHCSTORM_H
#define NHCSTORM_H

#include <string>
#include <vector>
#include "nhc/NhcStormDetails.h"
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/TwoWidgetScroll.h"
#include "ui/Photo.h"
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::string;
using std::vector;

class NhcStorm : public Window {
public:
    NhcStorm(QWidget *, const NhcStormDetails&);

private:
    void reload();
    void changeProduct();
    void launchGoes();
    QWidget * parent;
    NhcStormDetails stormData;
    VBox boxText;
    VBox boxImages;
    VBox box;
    TwoWidgetScroll sw;
    vector<Photo> images;
    vector<string> urls;
    ComboBox comboboxProduct;
    Button goesButton;
    Text text;
    string goesUrl;
    string product;
};

#endif  // NHCSTORM_H
