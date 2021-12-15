// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Text.h"
#include "settings/UIPreferences.h"

Text::Text() {
}

Text::Text(QWidget * parent, QString text) {
    this->parent = parent;
    textView = new QLabel(parent);
    textView->setText(text);
    textView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    textView->setWordWrap(true);
    textView->setTextFormat(Qt::PlainText);
    textView->setTextInteractionFlags(Qt::TextSelectableByMouse);
    this->text = text;
}

QLabel * Text::get() {
    return textView;
}

void Text::setWordWrap(bool c) {
    textView->setWordWrap(c);
}

void Text::setWrap(bool c) {
    textView->setWordWrap(c);
}

void Text::setText(const QString& text) {
    textView->setText(text);
    textView->adjustSize();
    this->text = text;
}

void Text::setFixedWidth() {
    auto font = QFont("Monospace");
    font.setStyleHint(QFont::TypeWriter);
    textView->setFont(font);
}

void Text::setBlue() {
    textView->setStyleSheet("QLabel { color : blue; }");
}

void Text::setGray() {
    textView->setStyleSheet("QLabel {color: gray;}");
}

void Text::setBold() {
    QFont font = textView->font();
    font.setBold(true);
    textView->setFont(font);
}

void Text::setBlueOnWhite() {
    textView->setStyleSheet("QLabel {background-color: white; color: black; font-size: 18px;}");
}

void Text::setVisible(bool b) {
    textView->setVisible(b);
}

void Text::setMainText() {
    textView->setTextInteractionFlags(Qt::TextSelectableByMouse);
    textView->setContentsMargins(UIPreferences::textPadding);
}

void Text::setStyleSheet(const QString& s) {
    textView->setStyleSheet(s);
}
