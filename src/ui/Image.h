// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef IMAGE_H
#define IMAGE_H

#include <functional>
#include <QByteArray>
#include <QWidget>
#include "ui/ClickableLabel.h"
#include "ui/Widget2.h"

using std::function;

class Image : public Widget2 {
public:
    Image();  // needed for MainWindow
    explicit Image(QWidget *);
    ClickableLabel * getView();
    void setBytes(const QByteArray&);
    void setToWidth(const QByteArray&, int);
    void setNumberAcross(int);
    void connect(const function<void()>&);
    int imageSize{};

private:
    QWidget * parent{};
    ClickableLabel * image{};
};

#endif  // IMAGE_H
