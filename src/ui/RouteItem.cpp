// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/RouteItem.h"

RouteItem::RouteItem() {
}

RouteItem::RouteItem(const QString& iconString, const QString& toolTip, std::function<void()> fn) {
    this->iconString = iconString;
    this->toolTip = toolTip;
    this->fn = fn;
}
