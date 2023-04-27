// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <functional>
#include <string>
#include <vector>
#include <QComboBox>
#include "ui/Widget2.h"

using std::function;
using std::string;
using std::vector;

class ComboBox : public Widget2 {
public:
    explicit ComboBox(QWidget *);
    ComboBox(QWidget *, const vector<string>&);
    void setIndex(int);
    int getIndex() const;
    void setIndexByPref(const string&, int);
    void setIndexByValue(const string&);
    void setArrayListInt(const vector<int>&);
    void setList(const vector<string>&);
    void addItems(const vector<string>&);
    void appendText(const string&);
    void clear();
    void block();
    void unblock();
    void connect(const function<void()>&);
    QComboBox * getView();
    void setVisible(bool);
    string getValue() const;

private:
    void blockSignals(bool);
    QComboBox * comboBox;
    QWidget * parent;
    QStringList comboItems;
};

#endif  // COMBOBOX_H
