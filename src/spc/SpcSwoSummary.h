// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCSWOSUMMARY_H
#define SPCSWOSUMMARY_H

#include <string>
#include <vector>
#include "ui/ScrolledWindow.h"
#include "ui/Shortcut.h"
#include "ui/Window.h"

using std::string;
using std::vector;

class SpcSwoSummary : public Window {
public:
    explicit SpcSwoSummary(QWidget *);

private:
    VBox box;
    vector<string> urls;
    vector<Image> images;
    const vector<string> day1to3List{"1", "2", "3"};
    const vector<string> day4To8List{"4", "5", "6", "7", "8"};
    ScrolledWindow sw;
    vector<Shortcut> shortcuts;
};

#endif  // SPCSWOSUMMARY_H
