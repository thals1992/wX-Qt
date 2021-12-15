// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef FUTUREVOID_H
#define FUTUREVOID_H

#include <functional>
#include <QWidget>

class FutureVoid {
public:
    FutureVoid();
    FutureVoid(QWidget *, std::function<void()>, std::function<void()>);
};

#endif  // FUTUREVOID_H
