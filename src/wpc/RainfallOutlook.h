// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WPCRAINFALLOUTLOOK_H
#define WPCRAINFALLOUTLOOK_H

#include "ui/ObjectTwoWidgetScroll.h"
#include "ui/Photo.h"
#include "ui/Text.h"
#include "ui/Window.h"

class RainfallOutlook : public Window {
public:
    RainfallOutlook(QWidget *, int);

private:
    QString url;
    QString product;
    Photo photo;
    Text text;
    ObjectTwoWidgetScroll sw;
};

#endif  // WPCRAINFALLOUTLOOK_H
