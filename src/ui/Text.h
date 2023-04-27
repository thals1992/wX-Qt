// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTLABEL_H
#define OBJECTLABEL_H

#include <string>
#include <QLabel>
#include "ui/Widget2.h"

using std::string;

class Text : public Widget2 {
public:
    Text(); // needed for unordered_map in MainWindow
    explicit Text(QWidget *, const string& = "");
    // QLabel * get();
    QLabel * getView();
    void setWordWrap(bool);
    void setText(const QString&);
    void setText(const string&);
    void setFixedWidth();
    void setBlue();
    void setGray();
    void setBold();
    void setBlueOnWhite();
    void setVisible(bool);

private:
    QLabel * textView{};
    QString text;
};

#endif  // OBJECTLABEL_H
