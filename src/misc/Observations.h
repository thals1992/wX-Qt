// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBSERVATIONS_H
#define OBSERVATIONS_H

#include "ui/ComboBox.h"
#include "ui/Photo.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class Observations : public Window {
public:
    explicit Observations(QWidget *);

private:
    void reload();
    void changeProduct();
    const QString prefToken = "SFC_OBS_IMG_IDX";
    QString url = "";
    Photo photo;
    VBox box;
    ComboBox comboboxProduct;
    int index;
};

#endif  // OBSERVATIONS_H
