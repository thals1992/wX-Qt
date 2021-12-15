// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef ACTION_H
#define ACTION_H

#include <functional>
#include <QAction>

class Action {
public:
    Action();
    Action(const QString&, QObject *);
    QAction * get() const;
    void setCheckable(bool);
    void setChecked(bool);

private:
    QAction * qaction;
    QObject * parent;
};

#endif  // ACTION_H
