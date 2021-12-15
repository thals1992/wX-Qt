// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ComboBox.h"
#include "settings/UIPreferences.h"
#include "util/To.h"
#include "util/UtilityList.h"

ComboBox::ComboBox() {
}

ComboBox::ComboBox(QWidget * parent) {
    comboBox = new QComboBox(parent);
    this->parent = parent;
    comboBox->setMaxVisibleItems(UIPreferences::comboBoxSize);
    comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
}

ComboBox::ComboBox(QWidget * parent, QStringList list) {
    comboBox = new QComboBox(parent);
    this->parent = parent;
    comboBox->setMaxVisibleItems(UIPreferences::comboBoxSize);
    comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    comboBox->addItems(list);
    comboItems = list;
}

void ComboBox::setIndex(int index) {
    comboBox->setCurrentIndex(index);
}

int ComboBox::getIndex() const {
    return comboBox->currentIndex();
}

void ComboBox::setIndexByValue(const QString& item) {
    auto index = UtilityList::findex(item, comboItems);
    comboBox->setCurrentIndex(index);
}

void ComboBox::setArrayListInt(QVector<int> l) {
    for (auto i : l) {
        appendText(To::String(i));
    }
}

void ComboBox::setList(QStringList items) {
    comboBox->clear();
    comboItems.clear();
    comboItems += items;
    comboBox->addItems(items);
}

void ComboBox::addItems(QStringList list) {
    comboBox->addItems(list);
    comboItems = list;
}

void ComboBox::appendText(QString s) {
    comboItems.push_back(s);
    comboBox->addItem(s);
}

void ComboBox::clear() {
    comboBox->clear();
}

// GTK compat
void ComboBox::block([[maybe_unused]] int i) {
    blockSignals(true);
}

// GTK compat
void ComboBox::unblock([[maybe_unused]] int i) {
    blockSignals(false);
}

// GTK compat
void ComboBox::block() {
    blockSignals(true);
}

// GTK compat
void ComboBox::unblock() {
    blockSignals(false);
}

void ComboBox::blockSignals(bool b) {
    comboBox->blockSignals(b);
}

void ComboBox::connect(std::function<void()> f) {
    QObject::connect(get(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), parent, f);
}

QComboBox * ComboBox::get() {
    return comboBox;
}

void ComboBox::setVisible(bool b) {
    comboBox->setVisible(b);
}

void ComboBox::removeAll() {
    comboBox->clear();
    comboItems.clear();
}

QString ComboBox::currentText() const {
    return comboBox->currentText();
}

QString ComboBox::getValue() const {
    return comboBox->currentText();
}
