// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/TextViewer.h"
#include "objects/FutureText.h"

TextViewer::TextViewer(QWidget * parent, const string& url, int width, int height)
    : Window{parent}
    , sw{ ScrolledWindow{this, box} }
    , text{ Text{this} }
{
    if (width == 0 && height == 0) {
        maximize();
    } else {
        setSize(width, height);
    }
    box.addWidget(text);
    new FutureText{this, url, [this] (const auto& s) { text.setText(s); }};
}
