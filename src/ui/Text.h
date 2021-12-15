// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTLABEL_H
#define OBJECTLABEL_H

#include <QLabel>

class Text {
public:
    Text();
    Text(QWidget *, QString = "");
    QLabel * get();
    void setWordWrap(bool);
    void setWrap(bool);
    void setText(const QString& text);
    void setFixedWidth();
    void setBlue();
    void setGray();
    void setBold();
    void setBlueOnWhite();
    void setVisible(bool);
    void setMainText();
    void setStyleSheet(const QString&);

private:
    QWidget * parent;
    QLabel * textView;
    QString text;
};

#endif  // OBJECTLABEL_H
