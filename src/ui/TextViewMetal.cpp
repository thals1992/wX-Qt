// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/TextViewMetal.h"

float TextViewMetal::fontSize = 8.0;

void TextViewMetal::setText(const string& textF) {
    text = QString::fromStdString(textF);
}

void TextViewMetal::setPadding(double xPosF, double yPosF) {
    xPos = static_cast<int>(xPosF);
    yPos = static_cast<int>(yPosF);
}
