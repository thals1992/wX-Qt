// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ObjectTwoWidgetScroll.h"
#include <QScrollArea>

ObjectTwoWidgetScroll::ObjectTwoWidgetScroll() {
}

ObjectTwoWidgetScroll::ObjectTwoWidgetScroll(Window * parent, QWidget * w1, QWidget * w2) {
    vbox0 = VBox(parent);
    vbox0.addWidget(w1);
    vbox0.setAlignment(w1, Qt::AlignTop);

    vbox1 = VBox(parent);
    vbox1.addWidget(w2);

    hbox = HBox(parent);
    hbox.addLayout(vbox0.get());
    hbox.addLayout(vbox1.get());

    auto scrollArea = new QScrollArea(parent);
    scrollArea->setWidget(parent->centralWidget);
    scrollArea->setWidgetResizable(true);

    parent->setCentralWidget(scrollArea);
    parent->centralWidget->setLayout(hbox.get());
    parent->show();
}

ObjectTwoWidgetScroll::ObjectTwoWidgetScroll(Window * parent, QBoxLayout * w1, QWidget * w2) {
    vbox0 = VBox(parent);
    vbox0.addLayout(w1);

    vbox1 = VBox(parent);
    vbox1.addWidget(w2);
    vbox1.setAlignment(w2, Qt::AlignTop);

    hbox = HBox(parent);
    hbox.addLayout(vbox0.get());
    hbox.addLayout(vbox1.get());

    auto scrollArea = new QScrollArea(parent);
    scrollArea->setWidget(parent->centralWidget);
    scrollArea->setWidgetResizable(true);

    parent->setCentralWidget(scrollArea);
    parent->centralWidget->setLayout(hbox.get());
    parent->show();
}

ObjectTwoWidgetScroll::ObjectTwoWidgetScroll(Window * parent, QWidget * w1, QBoxLayout * w2) {
    vbox0 = VBox(parent);
    vbox0.addWidget(w1);
    vbox0.setAlignment(w1, Qt::AlignTop);

    vbox1 = VBox(parent);
    vbox1.addLayout(w2);

    hbox = HBox(parent);
    hbox.addLayout(vbox0.get());
    hbox.addLayout(vbox1.get());

    auto scrollArea = new QScrollArea(parent);
    scrollArea->setWidget(parent->centralWidget);
    scrollArea->setWidgetResizable(true);

    parent->setCentralWidget(scrollArea);
    parent->centralWidget->setLayout(hbox.get());
    parent->show();
}

ObjectTwoWidgetScroll::ObjectTwoWidgetScroll(Window * parent, QBoxLayout * w1, QBoxLayout * w2) {
    vbox0 = VBox(parent);
    vbox0.addLayout(w1);

    vbox1 = VBox(parent);
    vbox1.addLayout(w2);

    hbox = HBox(parent);
    hbox.addLayout(vbox0.get());
    hbox.addLayout(vbox1.get());

    auto scrollArea = new QScrollArea(parent);
    scrollArea->setWidget(parent->centralWidget);
    scrollArea->setWidgetResizable(true);

    parent->setCentralWidget(scrollArea);
    parent->centralWidget->setLayout(hbox.get());
    parent->show();
}
