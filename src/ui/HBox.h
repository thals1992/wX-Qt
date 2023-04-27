// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef HBOX_H
#define HBOX_H

#include <string>
#include <vector>
#include <QHBoxLayout>
#include "ui/Box.h"
#include "ui/Image.h"
#include "ui/Widget2.h"
#include "ui/Window.h"

using std::string;
using std::vector;

class HBox : public Box {
public:
    HBox();
    void addWidget(QWidget *, int = 0, Qt::Alignment = Qt::Alignment());
    void addWidget(Widget2&, int = 0, Qt::Alignment = Qt::Alignment());
    void addLayout(QLayout *, int = 0);
    void addLayout(Box&, int = 0);
    void addStretch();
    QHBoxLayout * getView();
    void setSpacing(int);
    void getAndShow(Window *);
    void addImageRow(QWidget *, const vector<string>&, vector<Image>&);
    void removeChildren();

private:
    QHBoxLayout * box;
};

#endif  // HBOX_H
