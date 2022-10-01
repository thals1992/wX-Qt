// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NHCSTORM_H
#define NHCSTORM_H

#include <string>
#include <vector>
#include "nhc/ObjectNhcStormDetails.h"
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/ObjectTwoWidgetScroll.h"
#include "ui/Photo.h"
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::string;
using std::vector;

class NhcStorm : public Window {
public:
    NhcStorm(QWidget *, const ObjectNhcStormDetails&);

private:
    void reload();
    void changeProduct();
    void launchGoes();
    QWidget * parent;
    ObjectNhcStormDetails stormData;
    VBox boxText;
    VBox boxImages;
    VBox box;
    ObjectTwoWidgetScroll sw;
    vector<Photo> images;
    vector<string> urls;
    ComboBox comboboxProduct;
    Button goesButton;
    Text text;
    string goesUrl;
    string product;
};

#endif  // NHCSTORM_H
