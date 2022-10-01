// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTTWOWIDGETSCROLL_H
#define OBJECTTWOWIDGETSCROLL_H

#include <QBoxLayout>
#include <QScrollArea>
#include "ui/HBox.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class ObjectTwoWidgetScroll {
public:
    ObjectTwoWidgetScroll(Window *, QWidget *, QWidget *);
    ObjectTwoWidgetScroll(Window *, QBoxLayout *, QWidget *);
    ObjectTwoWidgetScroll(Window *, QWidget *, QBoxLayout *);
    ObjectTwoWidgetScroll(Window *, QBoxLayout *, QBoxLayout *);

private:
    QScrollArea * scrollArea;
    VBox vbox0;
    VBox vbox1;
    HBox hbox;
};

#endif  // OBJECTTWOWIDGETSCROLL_H
