// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/TabWidget.h"

TabWidget::TabWidget(QWidget * parent)
    : parent{ parent }
    , tabWidget{ new QTabWidget{parent} }
{}

void TabWidget::addTab(QWidget * w, const string& label) {
    tabWidget->addTab(w, QString::fromStdString(label));
}

void TabWidget::connect(const function<void(int)>& fn) {
    QObject::connect(get(), &QTabWidget::currentChanged, parent, fn);
}

void TabWidget::setIndex(int index) {
    tabWidget->setCurrentIndex(index);
}

QTabWidget * TabWidget::get() {
    return tabWidget;
}
