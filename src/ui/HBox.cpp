// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/HBox.h"
#include "settings/UIPreferences.h"
#include "util/UtilityUI.h"
#include "util/UtilityList.h"

HBox::HBox() {
}

HBox::HBox(QWidget * parent) {
    this->parent = parent;
    box = new QHBoxLayout();
    box->setSpacing(UIPreferences::boxPadding);
    box->setContentsMargins(0, 0, 0, 0);
    box->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

void HBox::addWidget(QWidget * w, int stretch, Qt::Alignment alignment) {
    box->addWidget(w, stretch, alignment);
}

void HBox::addLayout(QLayout * w, int stretch) {
    box->addLayout(w, stretch);
}

void HBox::getAndShow(Window * win) {
    win->centralWidget->setLayout(get());
    win->show();
}

void HBox::setSpacing(int i) {
    box->setSpacing(i);
}

void HBox::alignCenterLeft() {
    box->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
}

QHBoxLayout * HBox::get() {
    return box;
}

void HBox::addImageRow(QStringList urls, QVector<Image>& images) {
    for (auto index : UtilityList::range(urls.size())) {
        auto image = Image::withIndex(parent, index);
        images.push_back(image);
        box->addWidget(image.get());
    }
}

void HBox::removeChildren() {
    UtilityUI::removeChildren(get());
}
