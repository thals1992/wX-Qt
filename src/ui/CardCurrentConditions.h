// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDCURRENTCONDITIONS_H
#define OBJECTCARDCURRENTCONDITIONS_H

#include <QWidget>
#include "ui/HBox.h"
#include "ui/Text.h"
#include "ui/Photo.h"
#include "ui/VBox.h"
#include "util/CurrentConditions.h"

class CardCurrentConditions : public HBox {
public:
    CardCurrentConditions();
    CardCurrentConditions(QWidget *, const CurrentConditions&);
    void update(const CurrentConditions&);

private:
    VBox boxText;
    Text topLine;
    Text middleLine;
    Text bottomLine;
    Photo photo;
};

#endif  // OBJECTCARDCURRENTCONDITIONS_H
