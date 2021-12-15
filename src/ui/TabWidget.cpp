// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/TabWidget.h"

TabWidget::TabWidget() {
}

TabWidget::TabWidget(QWidget * parent) {
    this->parent = parent;
    tabWidget = new QTabWidget(parent);
}

void TabWidget::addTab(QWidget * w, const QString& label) {
    tabWidget->addTab(w, label);
}

void TabWidget::connect(std::function<void(int)> fn) {
    QObject::connect(get(), &QTabWidget::currentChanged, parent, fn);
}

void TabWidget::setIndex(int index) {
    tabWidget->setCurrentIndex(index);
}

QTabWidget * TabWidget::get() {
    return tabWidget;
}
