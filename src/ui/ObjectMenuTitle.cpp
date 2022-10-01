// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectMenuTitle.h"

ObjectMenuTitle::ObjectMenuTitle(const string& title, int count)
    : title{ title }
    , count{ count }
{}

void ObjectMenuTitle::setList(const vector<string>& items, int index) {
    this->items = vector<string>{items.begin() + index, items.begin() + index + count};
}

vector<string> ObjectMenuTitle::get() const {
    return items;
}
