// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef VBOX_H
#define VBOX_H

#include <QVBoxLayout>
#include "ui/HBox.h"
#include "ui/Image.h"
#include "ui/Window.h"

class VBox {
public:
    VBox();
    explicit VBox(QWidget *);
    void addWidget(QWidget *, int = 0, Qt::Alignment = Qt::Alignment());
    void addWidgetAndCenter(QWidget *);
    void addWidgetAndCenterTop(QWidget *);
    void addLayout(QLayout *, int = 0);
    void addStretch();
    void setSpacing(int);
    void addMargins();
    void setAlignment(QWidget *, Qt::Alignment);
    void setAlignment(Qt::Alignment);
    void getAndShow(Window *);
    void removeChildren();
    void addImageRows(QStringList, QVector<Image>&, int);
    QVBoxLayout * get();

private:
    QVBoxLayout * box;
    QWidget * parent;
    QVector<HBox> boxRows;
};

#endif  // VBOX_H
