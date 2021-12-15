// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef LIGHTNING_H
#define LIGHTNING_H

#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/Photo.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class Lightning : public Window {
public:
    explicit Lightning(QWidget *);

private:
    void reload();
    void changeProduct(int);
    void changeTime(int);
    void changeSector();
    void changeTime();
    QString time;
    QString sector;
    const QString prefTokenSector = "LIGHTNING_SECTOR";
    const QString prefTokenPeriod = "LIGHTNING_PERIOD";
    ComboBox comboboxTime;
    ComboBox comboboxSector;
    HBox boxH;
    VBox box;
    Photo photo;
};

#endif  // LIGHTNING_H
