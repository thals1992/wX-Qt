// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TEXTVIEWERSTATICBOX_H
#define TEXTVIEWERSTATICBOX_H

#include <QString>
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Widget.h"

class TextViewerStaticBox : public Widget {
public:
    TextViewerStaticBox(QWidget *, const QString&);

private:
    VBox box;
    Text text;
};

#endif  // TEXTVIEWERSTATICBOX_H
