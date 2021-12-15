// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCSTORMREPORTS_H
#define SPCSTORMREPORTS_H

#include "spc/StormReport.h"
#include "ui/Calendar.h"
#include "ui/ComboBox.h"
#include "ui/ObjectCardStormReportItem.h"
#include "ui/Photo.h"
#include "ui/ScrolledWindow.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class SpcStormReports : public Window {
public:
    SpcStormReports(QWidget *, const QString&);

private:
    void onDateChanged();
    void updateReports(const QString&);
    void filterReports();
    void reload();
    QString spcStormReportsDay;
    QString url;
    QString stormReportsUrl;
    QStringList states;
    QVector<StormReport> stormReports;
    ScrolledWindow sw;
    VBox box;
    HBox boxImage;
    QVector<VBox> cardWidgets;
    Calendar calendar;
    Photo photo;
    VBox boxText;
    ComboBox stateMenu;
    Button lsrWfoButton;
};

#endif  // SPCSTORMREPORTS_H
