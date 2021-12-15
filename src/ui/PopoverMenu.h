// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef POPOVERMENU_H
#define POPOVERMENU_H

#include <functional>
#include <QPushButton>

class PopoverMenu {
public:
    PopoverMenu();
    PopoverMenu(QWidget *, const QString&, const QStringList&, std::function<void(QString)>);
    QPushButton * get();

private:
    QPushButton * button;
    QMenu * menu;
};

#endif  // POPOVERMENU_H
