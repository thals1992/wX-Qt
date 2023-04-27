// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTBUTTON_H
#define OBJECTBUTTON_H

#include <functional>
#include <string>
#include <QPushButton>
#include "ui/Icon.h"
#include "ui/Widget2.h"

using std::function;
using std::string;

class Button : public Widget2 {
public:
    Button(QWidget *, Icon, const string&);
    QPushButton * getView();
    void connect(const function<void()>&);
    void setText(const string&);
    string getText() const;
    void setVisible(bool);

private:
    QWidget * parent;
    QPushButton * button;
};

#endif  // OBJECTBUTTON_H
