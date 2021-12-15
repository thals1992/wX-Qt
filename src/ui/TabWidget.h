// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <functional>
#include <QTabWidget>

class TabWidget {
public:
    TabWidget();
    explicit TabWidget(QWidget * parent);
    void addTab(QWidget *, const QString&);
    void connect(std::function<void(int)>);
    void setIndex(int);
    QTabWidget * get();

private:
    QWidget * parent;
    QTabWidget * tabWidget;
};

#endif  // TABWIDGET_H
