// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/TextViewerStaticBox.h"

TextViewerStaticBox::TextViewerStaticBox(QWidget * parent, const QString& html) : Widget(parent) {
    box = VBox(this);
    text = Text(this, html);
    box.addWidget(text.get());
    setLayout(box.get());
}
