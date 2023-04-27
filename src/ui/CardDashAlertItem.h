// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDDASHALERTITEM_H
#define OBJECTCARDDASHALERTITEM_H

#include <QWidget>
#include "objects/ObjectWarning.h"
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/Text.h"
#include "ui/VBox.h"

class CardDashAlertItem : public HBox {
public:
    CardDashAlertItem(QWidget *, const ObjectWarning&);

private:
    VBox layoutVertical;
    VBox boxText;
    Text topLine;
    Text titleLine;
    Text startTimeLine;
    Text endTimeLine;
    Text middleLine;
    Button buttonDetails;
    Button buttonRadar;
};

#endif  // OBJECTCARDDASHALERTITEM_H
