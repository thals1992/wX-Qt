// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OPC_H
#define OPC_H

#include <string>
#include "ui/ComboBox.h"
#include "ui/Photo.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::string;

class Opc : public Window {
public:
    explicit Opc(QWidget *);

private:
    void reload();
    void changeProduct();
    const string prefToken{"OPC_IMG_FAV_URL"};
    Photo photo;
    VBox box;
    ComboBox comboboxProduct;
    int index;
};

#endif  // OPC_H
