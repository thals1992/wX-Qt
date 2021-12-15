// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectCardBlackHeaderText.h"

ObjectCardBlackHeaderText::ObjectCardBlackHeaderText(QWidget * parent, const QString& row1) : VBox(parent) {
    firstRow = Text(parent, row1);
    firstRow.setBlueOnWhite();
    addWidget(firstRow.get());
}
