// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Action.h"

Action::Action(const string& label, QObject * parent)
    : qaction{ new QAction{QString::fromStdString(label), parent} }
{}

QAction * Action::get() const {
    return qaction;
}
