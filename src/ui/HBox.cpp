// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/HBox.h"
#include "settings/UIPreferences.h"
#include "util/UtilityUI.h"
#include "util/UtilityList.h"

HBox::HBox()
    : box{ new QHBoxLayout{} }
{
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

void HBox::addStretch() {
    box->addStretch();
}

void HBox::getAndShow(Window * win) {
    win->centralWidget->setLayout(get());
    win->show();
}

void HBox::setSpacing(int i) {
    box->setSpacing(i);
}

QHBoxLayout * HBox::get() {
    return box;
}

void HBox::addImageRow(QWidget * parent, const vector<string>& urls, vector<Image>& images) {
    for ([[maybe_unused]] auto index : range(urls.size())) {
        images.emplace_back(parent);
        box->addWidget(images.back().get());
    }
}

void HBox::removeChildren() {
    UtilityUI::removeChildren(get());
}
