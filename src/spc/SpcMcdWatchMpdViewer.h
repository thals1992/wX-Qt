// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCMCDWATCHMPDVIEWER_H
#define SPCMCDWATCHMPDVIEWER_H

#include "ui/Button.h"
#include "ui/Photo.h"
#include "ui/ObjectTwoWidgetScroll.h"
#include "ui/Text.h"
#include "ui/Window.h"

class SpcMcdWatchMpdViewer : public Window {
public:
    SpcMcdWatchMpdViewer(QWidget *, const QString&);

private:
    QWidget * parent;
    void updateText(QString);
    Button button;
    VBox boxText;
    Text text;
    QString url;
    QString token = "";
    ObjectTwoWidgetScroll sw;
    Photo photo;
};

#endif  // SPCMCDWATCHMPDVIEWER_H
