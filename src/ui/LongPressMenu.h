// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef LONGPRESSMENU_H
#define LONGPRESSMENU_H

#include <functional>
#include <vector>
#include <QMenu>
#include <QPoint>
#include "ui/Action.h"
#include "ui/CMenuItem.h"

using std::vector;

class LongPressMenu {
public:
    explicit LongPressMenu(QWidget *);
    void add(const CMenuItem&);
    void show(const QPoint&);

private:
    QWidget * parent;
    QMenu * contextMenu;
    vector<CMenuItem> cmenuItems;
    vector<Action> actions;
};

#endif  // LONGPRESSMENU_H
