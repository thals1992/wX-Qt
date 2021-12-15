// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <functional>
#include <QShortcut>
#include <QWidget>

class Shortcut {
public:
    Shortcut();
    Shortcut(const QKeySequence&, QWidget *);
    QShortcut * get();
    void connect(std::function<void()>);

private:
    QShortcut * qshortcut;
    QWidget * parent;
};

#endif  // SHORTCUT_H
