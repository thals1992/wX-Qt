// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "ui/Shortcut.h"

class Window : public QMainWindow {
public:
    explicit Window(QWidget *);
    void setSize(int, int);
    void maximize();
    void setTitle(const QString&);
    QWidget * centralWidget;

private:
    Shortcut shortcutClose;
    Shortcut shortcutClose2;
};

#endif  // WINDOW_H
