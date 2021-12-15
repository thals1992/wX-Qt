// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef HBOX_H
#define HBOX_H

#include <QHBoxLayout>
#include "ui/Image.h"
#include "ui/Window.h"

class HBox {
public:
    HBox();
    explicit HBox(QWidget *);
    void addWidget(QWidget *, int = 0, Qt::Alignment = Qt::Alignment());
    void addLayout(QLayout *, int = 0);
    QHBoxLayout * get();
    void alignCenterLeft();
    void setSpacing(int);
    void getAndShow(Window *);
    void addImageRow(QStringList, QVector<Image>&);
    void removeChildren();

private:
    QHBoxLayout * box;
    QWidget * parent;
};

#endif  // HBOX_H
