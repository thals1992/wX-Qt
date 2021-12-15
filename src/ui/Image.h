// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef IMAGE_H
#define IMAGE_H

#include <functional>
#include <QByteArray>
#include <QString>
#include <QWidget>
#include "ui/ClickableLabel.h"

class Image {
public:
    Image();
    explicit Image(QWidget * parent);
    static Image withIndex(QWidget *, int);
    ClickableLabel * get();
    void setBytes(QByteArray);
    void setToWidth(QByteArray, int);
    void setNumberAcross(int);
    void connect(std::function<void()>);
    int index = 0;
    int imageSize;

private:
    QWidget * parent;
    ClickableLabel * image;
};

#endif  // IMAGE_H
