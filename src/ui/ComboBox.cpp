// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ComboBox.h"
#include "settings/UIPreferences.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityList.h"
#include "util/UtilityUI.h"

ComboBox::ComboBox(QWidget * parent)
    : comboBox{ new QComboBox{parent} }
    , parent{ parent }
{
    comboBox->setMaxVisibleItems(UIPreferences::comboBoxSize);
    comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
}

ComboBox::ComboBox(QWidget * parent, const vector<string>& items)
    : comboBox{ new QComboBox{parent} }
    , parent{ parent }
{
    for (const auto& s : items) {
        comboItems.push_back(QString::fromStdString(s));
    }
    comboBox->setMaxVisibleItems(UIPreferences::comboBoxSize);
    comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    comboBox->addItems(comboItems);
    if (UtilityUI::isMobile()) {
        comboBox->setFixedWidth(100);
    }
}

void ComboBox::setIndex(int index) {
    comboBox->setCurrentIndex(index);
}

int ComboBox::getIndex() const {
    return comboBox->currentIndex();
}

void ComboBox::setIndexByPref(const string& s, int i) {
    setIndex(Utility::readPrefInt(s, i));
}

void ComboBox::setIndexByValue(const string& item) {
    const auto index = findex(item, comboItems);
    comboBox->setCurrentIndex(index);
}

void ComboBox::setArrayListInt(const vector<int>& items) {
    for (auto i : items) {
        appendText(To::string(i));
    }
}

void ComboBox::setList(const vector<string>& items) {
    comboBox->clear();
    comboItems.clear();
    for (const auto& s : items) {
        comboItems.push_back(QString::fromStdString(s));
    }
    comboBox->addItems(comboItems);
}

void ComboBox::addItems(const vector<string>& items) {
    comboItems.clear();
    for (const auto& s : items) {
        comboItems.push_back(QString::fromStdString(s));
    }
    comboBox->addItems(comboItems);
}

void ComboBox::appendText(const string& s) {
    comboItems.push_back(QString::fromStdString(s));
    comboBox->addItem(QString::fromStdString(s));
}

void ComboBox::clear() {
    comboBox->clear();
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

void ComboBox::connect(const function<void()>& fn) {
    QObject::connect(comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), parent, fn);
}

QComboBox * ComboBox::getView() {
    return comboBox;
}

void ComboBox::setVisible(bool b) {
    comboBox->setVisible(b);
}

string ComboBox::getValue() const {
    return comboBox->currentText().toStdString();
}
