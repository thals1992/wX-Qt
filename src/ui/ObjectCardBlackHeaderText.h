// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDBLACKHEADERTEXT_H
#define OBJECTCARDBLACKHEADERTEXT_H

#include <QWidget>
#include "ui/Text.h"
#include "ui/VBox.h"

class ObjectCardBlackHeaderText : public VBox {
public:
    ObjectCardBlackHeaderText(QWidget *, const QString&);

private:
    Text firstRow;
};

#endif  // OBJECTCARDBLACKHEADERTEXT_H
