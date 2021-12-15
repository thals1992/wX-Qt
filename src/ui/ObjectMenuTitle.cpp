// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectMenuTitle.h"

ObjectMenuTitle::ObjectMenuTitle() {
}

ObjectMenuTitle::ObjectMenuTitle(const QString& title, int count) {
    this->title = title;
    this->count = count;
}

void ObjectMenuTitle::setList(const QStringList& items, int index) {
    this->items = items.mid(index, count);
}

QStringList ObjectMenuTitle::get() {
    return items;
}
