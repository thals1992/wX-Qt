// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef COLORTEXTBOX_H
#define COLORTEXTBOX_H

#include <QLabel>

class ColorTextBox {
public:
    ColorTextBox();
    ColorTextBox(QWidget * parent);
    void setText(const QString& s);
    void setBackGroundRed();
    void setBackGroundGreen();
    QLabel * get();

private:
    QLabel * label;
};

#endif  // COLORTEXTBOX_H
