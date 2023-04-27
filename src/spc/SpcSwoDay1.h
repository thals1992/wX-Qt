// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCSWODAY1_H
#define SPCSWODAY1_H

#include <string>
#include <vector>
#include "ui/TwoWidgetScroll.h"
#include "ui/Photo.h"
#include "ui/Text.h"
#include "ui/Window.h"

using std::string;
using std::vector;

class SpcSwoDay1 : public Window {
public:
    SpcSwoDay1(QWidget *, const string&);

private:
    VBox imageVBox;
    Text text;
    TwoWidgetScroll sw;
    vector<string> urls;
    vector<Image> images;
};

#endif  // SPCSWODAY1_H
