// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCSWODAY1_H
#define SPCSWODAY1_H

#include "ui/ObjectTwoWidgetScroll.h"
#include "ui/Photo.h"
#include "ui/Text.h"
#include "ui/Window.h"

class SpcSwoDay1 : public Window {
public:
    SpcSwoDay1(QWidget *, const QString&);

private:
    QVector<Photo> images;
    QStringList urls;
    VBox imageVBox;
    QString product;
    Text text;
    ObjectTwoWidgetScroll sw;
};

#endif  // SPCSWODAY1_H
