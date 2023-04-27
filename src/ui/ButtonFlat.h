// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTBUTTONFLAT_H
#define OBJECTBUTTONFLAT_H

#include <functional>
#include <string>
#include <QPushButton>
#include "ui/Widget2.h"

using std::function;
using std::string;

class ButtonFlat : public Widget2 {
public:
    ButtonFlat(const string&, const string&, QWidget *);
    QPushButton * getView();
    void connect(const function<void()>&);
    void setText(const string&);
    void setVisible(bool);
    void refresh();
    static int iconSize;

private:
    QWidget * parent;
    QPushButton * button;
};

#endif  // OBJECTBUTTONFLAT_H
