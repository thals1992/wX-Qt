// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/VBox.h"
#include "settings/UIPreferences.h"
#include "util/UtilityList.h"
#include "util/UtilityUI.h"

VBox::VBox() {
    box = new QVBoxLayout();
    box->setSpacing(UIPreferences::boxPadding);
    box->setContentsMargins(0, 0, 0, 0);
    // box->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

VBox::VBox(QWidget * parent) {
    this->parent = parent;
    box = new QVBoxLayout();
    box->setSpacing(UIPreferences::boxPadding);
    box->setContentsMargins(0, 0, 0, 0);
    // box->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

void VBox::getAndShow(Window * win) {
    win->centralWidget->setLayout(get());
    win->show();
}

void VBox::addWidget(QWidget * w, int stretch, Qt::Alignment alignment) {
    box->addWidget(w, stretch, alignment);
}

void VBox::addWidgetAndCenter(QWidget * w) {
    box->addWidget(w);
    box->setAlignment(w, Qt::AlignHCenter);
}

void VBox::addWidgetAndCenterTop(QWidget * w) {
    box->addWidget(w);
    box->setAlignment(w, Qt::AlignTop | Qt::AlignHCenter);
}

void VBox::addLayout(QLayout * w, int stretch) {
    box->addLayout(w, stretch);
}

void VBox::addStretch() {
    box->addStretch();
}

void VBox::addMargins() {
    box->setContentsMargins(UIPreferences::textPadding);
}

void VBox::setSpacing(int i) {
    box->setSpacing(i);
}

// https://doc.qt.io/qt-5/qt.html#AlignmentFlag-enum
void VBox::setAlignment(QWidget * w, Qt::Alignment alignment) {
    box->setAlignment(w, alignment);
}

void VBox::setAlignment(Qt::Alignment alignment) {
    box->setAlignment(alignment);
}

void VBox::removeChildren() {
    UtilityUI::removeChildren(get());
}

void VBox::addImageRows(QStringList urls, QVector<Image>& images, int imagesAcross) {
    for (auto index : UtilityList::range(urls.size())) {
        images.push_back(Image::withIndex(parent, index));
        if ((boxRows.size() <= static_cast<int>(index / imagesAcross))) {
            boxRows.push_back(HBox(parent));
        }
        boxRows.back().addWidget(images.back().get());
    }
    for (auto& b : boxRows) {
        box->addLayout(b.get());
    }
}

QVBoxLayout * VBox::get() {
    return box;
}
