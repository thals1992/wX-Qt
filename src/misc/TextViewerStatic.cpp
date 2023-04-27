// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/TextViewerStatic.h"

TextViewerStatic::TextViewerStatic(QWidget * parent, const string& html, int width, int height)
    : Window{parent}
    , sw{ ScrolledWindow{this, box} }
    , text{ Text{this, html} }
{
    if (width == 0 && height == 0) {
        maximize();
    } else {
        setSize(width, height);
    }
    box.addWidget(text);
}
