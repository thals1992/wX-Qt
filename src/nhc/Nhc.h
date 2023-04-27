// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NHC_H
#define NHC_H

#include <memory>
#include <string>
#include <vector>
#include "nhc/ObjectNhc.h"
#include "nhc/CardNhcStormReportItem.h"
#include "ui/ScrolledWindow.h"
#include "ui/Window.h"

using std::string;
using std::vector;

class Nhc : public Window {
public:
    explicit Nhc(QWidget *);

private:
    VBox boxText;
    VBox box;
    ScrolledWindow sw;
    vector<Image> images;
    vector<string> urls;
    ObjectNhc objectNhc;
    vector<std::unique_ptr<CardNhcStormReportItem>> stormCards;
};

#endif  // NHC_H
