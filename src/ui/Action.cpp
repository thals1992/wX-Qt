// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Action.h"

Action::Action() {
}

Action::Action(const QString& label, QObject * parent) {
    this->parent = parent;
    qaction = new QAction(label, parent);
}

QAction * Action::get() const {
    return qaction;
}
