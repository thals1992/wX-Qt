// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NHC_H
#define NHC_H

#include "nhc/ObjectNhc.h"
#include "nhc/ObjectCardNhcStormReportItem.h"
#include "ui/ScrolledWindow.h"
#include "ui/Window.h"

class Nhc : public Window {
public:
    explicit Nhc(QWidget *);

private:
    VBox boxText;
    QVector<Image> images;
    QStringList urls;
    VBox box;
    ScrolledWindow sw;
    ObjectNhc objectNhc;
    QVector<ObjectCardNhcStormReportItem *> stormCards;
};

#endif  // NHC_H
