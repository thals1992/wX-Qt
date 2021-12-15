// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDLOCATIONITEM_H
#define OBJECTCARDLOCATIONITEM_H

#include <QWidget>
#include "ui/HBox.h"
#include "ui/Text.h"
#include "ui/VBox.h"

class ObjectCardLocationItem : public VBox {
public:
    ObjectCardLocationItem();
    explicit ObjectCardLocationItem(QWidget *, int);

private:
    HBox hbox;
    Text text1;
    Text text2;
    Text text3;
    Text text4;
};

#endif  // OBJECTCARDLOCATIONITEM_H
