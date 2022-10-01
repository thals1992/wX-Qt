// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDHAZARDS_H
#define OBJECTCARDHAZARDS_H

#include <string>
#include <vector>
#include <QWidget>
#include "ui/Button.h"
#include "ui/VBox.h"
#include "util/ObjectHazards.h"

using std::string;
using std::vector;

class ObjectCardHazards : public VBox {
public:
    explicit ObjectCardHazards();
    ObjectCardHazards(QWidget *, const ObjectHazards&);
    void removeLabels();

private:
    VBox vbox;
    string data;
    vector<Button> labels;
};

#endif  // OBJECTCARDHAZARDS_H
