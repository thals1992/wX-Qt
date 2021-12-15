// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCFIREWEATHEROUTLOOK_H
#define SPCFIREWEATHEROUTLOOK_H

#include "ui/ObjectTwoWidgetScroll.h"
#include "ui/Photo.h"
#include "ui/Text.h"
#include "ui/Window.h"

class SpcFireWeatherOutlook : public Window {
public:
    SpcFireWeatherOutlook(QWidget *, int);

private:
    QString url;
    QString product;
    Photo photo;
    Text text;
    ObjectTwoWidgetScroll sw;
};

#endif  // SPCFIREWEATHEROUTLOOK_H
