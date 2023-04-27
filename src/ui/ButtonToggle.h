// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef BUTTONTOGGLE_H
#define BUTTONTOGGLE_H

#include <functional>
#include <string>
#include <QPushButton>
#include "ui/Icon.h"
#include "ui/Widget2.h"

using std::function;
using std::string;

class ButtonToggle : public Widget2 {
public:
    ButtonToggle(QWidget *, Icon, const string&);
    void connect(const function<void()>&);
    void setText(const string&);
    void setVisible(bool);
    void setCheckable(bool);
    void setChecked(bool);
    bool isChecked();
    void setActive(bool);
    QPushButton * getView();

private:
    QWidget * parent;
    QPushButton * button;
};

#endif  // BUTTONTOGGLE_H
