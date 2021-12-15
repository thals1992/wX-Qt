// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBSERVATIONSITES_H
#define OBSERVATIONSITES_H

#include "ui/Button.h"
#include "ui/HBox.h"
#include "ui/Window.h"

class ObservationSites : public Window {
public:
    explicit ObservationSites(QWidget *);

private slots:
    void launchAlert(const QString&);
    HBox box;
    Button button1;
    Button button2;
};

#endif  // OBSERVATIONSITES_H
