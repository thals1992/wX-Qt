// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTBUTTONFLAT_H
#define OBJECTBUTTONFLAT_H

#include <functional>
#include <QPushButton>

class ButtonFlat {
public:
    ButtonFlat();
    ButtonFlat(QString, QString, QWidget *);
    QPushButton * get();
    void connect(std::function<void()>);
    void setText(const QString&);
    QString getText() const;
    void setVisible(bool);
    void setCheckable(bool);
    void setChecked(bool);

private:
    QWidget * parent;
    QPushButton * button;
};

#endif  // OBJECTBUTTONFLAT_H
