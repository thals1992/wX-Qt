// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef ALERTSDETAIL_H
#define ALERTSDETAIL_H

#include "misc/CapAlert.h"
#include "ui/Text.h"
#include "ui/Window.h"
#include "ui/ScrolledWindow.h"

class AlertsDetail : public Window {
public:
    AlertsDetail(QWidget *, const QString&);

private:
    void download();
    void updateText();
    Text text;
    CapAlert capAlert;
    QString url;
    VBox box;
    ScrolledWindow sw;
};

#endif  // ALERTSDETAIL_H
