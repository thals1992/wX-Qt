// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDDASHALERTITEM_H
#define OBJECTCARDDASHALERTITEM_H

#include <QString>
#include <QWidget>
#include "objects/ObjectWarning.h"
#include "ui/HBox.h"
#include "ui/Button.h"
#include "ui/Text.h"
#include "ui/VBox.h"

class ObjectCardDashAlertItem : public HBox {
public:
    ObjectCardDashAlertItem(QWidget *, const ObjectWarning&);

private:
    QWidget * parent;
    VBox layoutVertical;
    VBox textLayout;
    Button buttonDetails;
    Button buttonRadar;
    Text topLine;
    Text titleLine;
    Text middleLine;
    Text startTimeLine;
    Text endTimeLine;
};

#endif  // OBJECTCARDDASHALERTITEM_H
