// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCCOMPMAP_H
#define SPCCOMPMAP_H

#include "ui/ComboBox.h"
#include "ui/Photo.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class SpcCompMap : public Window {
public:
    explicit SpcCompMap(QWidget *);

private:
    void reload();
    void changeProduct();
    QString product;
    const QString prefToken = "SPCCOMPMAP_LAYERSTRIOS";
    Photo photo;
    ComboBox comboboxProduct;
    VBox box;
};

#endif  // SPCCOMPMAP_H
