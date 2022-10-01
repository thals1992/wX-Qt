// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBSERVATIONSITES_H
#define OBSERVATIONSITES_H

#include <string>
#include "ui/Button.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::string;

class ObservationSites : public Window {
public:
    explicit ObservationSites(QWidget *);

private:
    static void launchAlert(const string&);
    VBox box;
    Button button1;
    Button button2;
};

#endif  // OBSERVATIONSITES_H
