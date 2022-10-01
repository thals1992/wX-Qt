// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Window.h"
#include "util/UtilityUI.h"

Window::Window(QWidget * parent)
    : QMainWindow{parent}
    , centralWidget{ new QWidget{this} }
    , shortcutClose{ Shortcut{QKeySequence{"Ctrl+W"}, this} }
    , shortcutClose2{ Shortcut{QKeySequence{Qt::Key_Escape}, this} }
{
    setCentralWidget(centralWidget);
    shortcutClose.connect([this] { close(); });
    shortcutClose2.connect([this] { close(); });
    maximize();
}

void Window::setSize(int x, int y) {
    resize(x, y);
    move(0, 0);
}

void Window::maximize() {
    const auto dimensions = UtilityUI::getScreenBounds();
    resize(dimensions[0], dimensions[1]);
    move(0, 0);
    // showMaximized();
}

void Window::setTitle(const string& s) {
    setWindowTitle(QString::fromStdString(s));
}
