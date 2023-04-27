// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCSTORMREPORTS_H
#define SPCSTORMREPORTS_H

#include <string>
#include <vector>
#include "spc/StormReport.h"
#include "ui/Calendar.h"
#include "ui/ComboBox.h"
#include "ui/CardStormReportItem.h"
#include "ui/Photo.h"
#include "ui/ScrolledWindow.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::string;
using std::vector;

class SpcStormReports : public Window {
public:
    SpcStormReports(QWidget *, const string&);

private:
    void onDateChanged();
    void updateReports(const string&);
    void filterReports();
    void reload();
    VBox box;
    HBox boxImage;
    VBox boxText;
    ScrolledWindow sw;
    Calendar calendar;
    Photo photo;
    ComboBox comboBox;
    Button lsrWfoButton;
    vector<VBox> cardWidgets;
    string spcStormReportsDay;
    string url;
    string stormReportsUrl;
    vector<string> states;
    vector<StormReport> stormReports;
};

#endif  // SPCSTORMREPORTS_H
