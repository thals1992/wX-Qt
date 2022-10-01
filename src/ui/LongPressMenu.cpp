// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/LongPressMenu.h"
#include "util/UtilityList.h"

LongPressMenu::LongPressMenu(QWidget * parent)
    : parent{ parent }
    , contextMenu{ new QMenu{parent} }
{}

void LongPressMenu::add(const CMenuItem& cmenuItem) {
    cmenuItems.push_back(cmenuItem);
    actions.emplace_back(cmenuItem.label, parent);
    contextMenu->addAction(actions.back().get());
}

void LongPressMenu::show(const QPoint& posGlobal) {
    const QAction * selectedItem = contextMenu->exec(posGlobal);
    for (auto index : range(actions.size())) {
        if (selectedItem == actions[index].get()) {
            cmenuItems[index].fn();
        }
    }
}
