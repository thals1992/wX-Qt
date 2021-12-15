// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/TextViewer.h"
#include "objects/FutureText.h"

TextViewer::TextViewer(QWidget * parent, const QString& url, int width, int height) : Window(parent) {
    if (width == 0 && height == 0) {
        maximize();
    } else {
        setSize(width, height);
    }
    box = VBox(this);
    text = Text(this,"");
    box.addWidget(text.get());
    sw = ScrolledWindow(this, box);
    new FutureText(this, url, [this] (const auto& s) { text.setText(s); });
}
