// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TEXTVIEWERSTATIC_H
#define TEXTVIEWERSTATIC_H

#include "ui/ScrolledWindow.h"
#include "ui/Text.h"
#include "ui/Window.h"

class TextViewerStatic : public Window {
public:
    TextViewerStatic(QWidget *, const QString&, int = 0, int = 0);

private:
    VBox box;
    Text text;
    ScrolledWindow sw;
};

#endif  // TEXTVIEWERSTATIC_H
