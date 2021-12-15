// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/TextViewMetal.h"

float TextViewMetal::fontSize = 8.0;

TextViewMetal::TextViewMetal() {
}

void TextViewMetal::setText(const QString& textF) {
    text = textF;
}

void TextViewMetal::setPadding(float xPosF, float yPosF) {
    xPos = static_cast<int>(xPosF);
    yPos = static_cast<int>(yPosF);
}
