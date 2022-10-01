// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ObjectTwoWidgetScroll.h"
#include <QScroller>
#include <QScrollArea>
#include "util/UtilityUI.h"

ObjectTwoWidgetScroll::ObjectTwoWidgetScroll(Window * parent, QWidget * w1, QWidget * w2)
    : scrollArea{ new QScrollArea{parent} }
{
    vbox0.addWidget(w1);
    vbox0.setAlignment(w1, Qt::AlignTop);

    vbox1.addWidget(w2);

    hbox.addLayout(vbox0.get());
    hbox.addLayout(vbox1.get());

    scrollArea->setWidget(parent->centralWidget);
    scrollArea->setWidgetResizable(true);

    if (UtilityUI::isMobile()) {
        QScroller::grabGesture(scrollArea->viewport(), QScroller::TouchGesture);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } else {
        QScroller::grabGesture(scrollArea->viewport(), QScroller::LeftMouseButtonGesture);
    }
    parent->setCentralWidget(scrollArea);
    parent->centralWidget->setLayout(hbox.get());
    parent->show();
}

ObjectTwoWidgetScroll::ObjectTwoWidgetScroll(Window * parent, QBoxLayout * w1, QWidget * w2)
    : scrollArea{ new QScrollArea{parent} }
{
    vbox0.addLayout(w1);
    vbox0.addStretch();

    vbox1.addWidget(w2);
    vbox1.setAlignment(w2, Qt::AlignTop);

    hbox.addLayout(vbox0.get());
    hbox.addLayout(vbox1.get());

    scrollArea->setWidget(parent->centralWidget);
    scrollArea->setWidgetResizable(true);

    if (UtilityUI::isMobile()) {
        QScroller::grabGesture(scrollArea->viewport(), QScroller::TouchGesture);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } else {
        QScroller::grabGesture(scrollArea->viewport(), QScroller::LeftMouseButtonGesture);
    }
    parent->setCentralWidget(scrollArea);
    parent->centralWidget->setLayout(hbox.get());
    parent->show();
}

ObjectTwoWidgetScroll::ObjectTwoWidgetScroll(Window * parent, QWidget * w1, QBoxLayout * w2)
    : scrollArea{ new QScrollArea{parent} }
{
    vbox0.addWidget(w1);
    vbox0.setAlignment(w1, Qt::AlignTop);

    vbox1.addLayout(w2);

    hbox.addLayout(vbox0.get());
    hbox.addLayout(vbox1.get());

    scrollArea->setWidget(parent->centralWidget);
    scrollArea->setWidgetResizable(true);

    if (UtilityUI::isMobile()) {
        QScroller::grabGesture(scrollArea->viewport(), QScroller::TouchGesture);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } else {
        QScroller::grabGesture(scrollArea->viewport(), QScroller::LeftMouseButtonGesture);
    }
    parent->setCentralWidget(scrollArea);
    parent->centralWidget->setLayout(hbox.get());
    parent->show();
}

ObjectTwoWidgetScroll::ObjectTwoWidgetScroll(Window * parent, QBoxLayout * w1, QBoxLayout * w2)
    : scrollArea{ new QScrollArea{parent} }
{
    vbox0.addLayout(w1);
    vbox1.addLayout(w2);

    hbox.addLayout(vbox0.get());
    hbox.addLayout(vbox1.get());

    scrollArea->setWidget(parent->centralWidget);
    scrollArea->setWidgetResizable(true);

    if (UtilityUI::isMobile()) {
        QScroller::grabGesture(scrollArea->viewport(), QScroller::TouchGesture);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    } else {
        QScroller::grabGesture(scrollArea->viewport(), QScroller::LeftMouseButtonGesture);
    }
    parent->setCentralWidget(scrollArea);
    parent->centralWidget->setLayout(hbox.get());
    parent->show();
}
