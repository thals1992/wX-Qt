// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDLOCATIONITEM_H
#define OBJECTCARDLOCATIONITEM_H

#include <QWidget>
#include "ui/HBox.h"
#include "ui/Text.h"
#include "ui/VBox.h"

class CardLocationItem : public VBox {
public:
    CardLocationItem(QWidget *, int);

private:
    VBox box;
    Text text1;
    Text text2;
};

#endif  // OBJECTCARDLOCATIONITEM_H
