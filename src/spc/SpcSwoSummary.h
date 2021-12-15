// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCSWOSUMMARY_H
#define SPCSWOSUMMARY_H

#include <QVector>
#include "ui/ScrolledWindow.h"
#include "ui/Shortcut.h"
#include "ui/Window.h"

class SpcSwoSummary : public Window {
public:
    explicit SpcSwoSummary(QWidget *);

private:
    void launch(int);
    VBox box;
    QVector<Image> images;
    QStringList urls;
    QStringList day1to3List = {"1", "2", "3"};
    QStringList day4To8List = {"4", "5", "6", "7", "8"};
    ScrolledWindow sw;
    QVector<Shortcut> shortcuts;
};

#endif  // SPCSWOSUMMARY_H
