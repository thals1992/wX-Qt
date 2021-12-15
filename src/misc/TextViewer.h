// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include "ui/ScrolledWindow.h"
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class TextViewer : public Window {
public:
    TextViewer(QWidget *, const QString&, int = 0, int = 0);

private:
    VBox box;
    Text text;
    ScrolledWindow sw;
};

#endif  // TEXTVIEWER_H
