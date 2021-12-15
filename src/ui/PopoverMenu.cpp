// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/PopoverMenu.h"
#include <QMenu>

PopoverMenu::PopoverMenu() {
}

PopoverMenu::PopoverMenu(QWidget * parent, const QString& buttonLabel, const QStringList& buttonList, std::function<void(QString)> fnAction) {
    button = new QPushButton(buttonLabel, parent);
    menu = new QMenu(parent);
    QObject::connect(menu, &QMenu::triggered, parent, [fnAction] (QAction * a) { fnAction(a->text()); });
    for (const auto& item : buttonList) {
        QAction * action = menu->addAction(item);
        action->setIconVisibleInMenu(false);
    }
    button->setMenu(menu);
}

QPushButton * PopoverMenu::get() {
    return button;
}
