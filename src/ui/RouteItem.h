// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef ROUTEITEM_H
#define ROUTEITEM_H

#include <functional>
#include <QString>

class RouteItem {
public:
    RouteItem();
    RouteItem(const QString&, const QString&, std::function<void()>);
    QString iconString;
    QString toolTip;
    std::function<void()> fn;
};

#endif  // ROUTEITEM_H
