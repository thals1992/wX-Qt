// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBSERVATIONS_H
#define OBSERVATIONS_H

#include <string>
#include "ui/ComboBox.h"
#include "ui/Photo.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::string;

class Observations : public Window {
public:
    explicit Observations(QWidget *);

private:
    void reload();
    const string prefToken{"SFC_OBS_IMG_IDX"};
    Photo photo;
    VBox box;
    ComboBox comboBox;
};

#endif  // OBSERVATIONS_H
