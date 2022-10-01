// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <functional>
#include <string>
#include <QTabWidget>

using std::function;
using std::string;

class TabWidget {
public:
    explicit TabWidget(QWidget *);
    void addTab(QWidget *, const string&);
    void connect(const function<void(int)>&);
    void setIndex(int);
    QTabWidget * get();

private:
    QWidget * parent;
    QTabWidget * tabWidget;
};

#endif  // TABWIDGET_H
