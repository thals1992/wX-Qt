// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef VBOX_H
#define VBOX_H

#include <string>
#include <vector>
#include <QVBoxLayout>
#include "ui/HBox.h"
#include "ui/Image.h"
#include "ui/Window.h"

using std::string;
using std::vector;

class VBox {
public:
    VBox();
    void addWidget(QWidget *, int = 0, Qt::Alignment = Qt::Alignment());
    void addWidgetAndCenter(QWidget *);
    void addLayout(QLayout *, int = 0);
    void addStretch();
    void setSpacing(int);
    void addMargins();
    void setAlignment(QWidget *, Qt::Alignment);
    void getAndShow(Window *);
    void removeChildren();
    void addImageRows(QWidget *, const vector<string>&, vector<Image>&, int);
    QVBoxLayout * get();

private:
    QVBoxLayout * box;
    vector<HBox> boxRows;
};

#endif  // VBOX_H
