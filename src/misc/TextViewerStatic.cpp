// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/TextViewerStatic.h"

TextViewerStatic::TextViewerStatic(QWidget * parent, const QString& html, int width, int height) : Window(parent) {
    if (width == 0 && height == 0) {
        maximize();
    } else {
        setSize(width, height);
    }
    box = VBox(this);
    text = Text(this, html);
    box.addWidget(text.get());
    sw = ScrolledWindow(this, box);
}
