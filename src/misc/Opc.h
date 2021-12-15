// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OPC_H
#define OPC_H

#include "ui/ComboBox.h"
#include "ui/Photo.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class Opc : public Window {
public:
    explicit Opc(QWidget *);

private:
    void reload();
    void changeProduct();
    const QString prefToken = "OPC_IMG_FAV_URL";
    QString url = "";
    Photo photo;
    VBox box;
    ComboBox comboboxProduct;
    int index;
};

#endif  // OPC_H
