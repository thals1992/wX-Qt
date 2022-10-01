// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RADARSTATUSBOX_H
#define RADARSTATUSBOX_H

#include <string>
#include <QLabel>
#include "ui/ClickableLabel.h"

using std::function;
using std::string;

class RadarStatusBox {
public:
    explicit RadarStatusBox(QWidget *);
    void setCurrent(const string&);
    void setOld(const string&);
    void connect(const function<void()>&);
    ClickableLabel * get();

private:
    void setText(const string&);
    void setBackGroundRed();
    void setBackGroundGreen();
    QWidget * parent;
    ClickableLabel * label;
};

#endif  // RADARSTATUSBOX_H
