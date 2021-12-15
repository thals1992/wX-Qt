// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <functional>
#include <QComboBox>

class ComboBox  {

public:
    ComboBox();
    explicit ComboBox(QWidget *);
    explicit ComboBox(QWidget *, QStringList);
    void setIndex(int);
    int getIndex() const;
    void setIndexByValue(const QString&);
    void setArrayListInt(QVector<int>);
    void setList(QStringList);
    void addItems(QStringList);
    void appendText(QString);
    void clear();
    void block(int);
    void unblock(int);
    void block();
    void unblock();
    void blockSignals(bool);
    void connect(std::function<void()> f);
    QComboBox * get();
    void setVisible(bool);
    void removeAll();
    QString currentText() const;
    QString getValue() const;

private:
    QComboBox * comboBox;
    QWidget * parent;
    QStringList comboItems;
};

#endif  // COMBOBOX_H
