// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/CardBlackHeaderText.h"

CardBlackHeaderText::CardBlackHeaderText(QWidget * parent, const string& row1)
    : firstRow{ Text{parent, row1} }
{
    firstRow.setBlueOnWhite();
    addWidget(firstRow);
}
