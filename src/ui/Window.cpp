// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/Window.h"
#include "util/UtilityUI.h"

Window::Window(QWidget * parent) : QMainWindow(parent) {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    shortcutClose = Shortcut(QKeySequence("Ctrl+W"), this);
    shortcutClose.connect([this] { close(); });

    shortcutClose2 = Shortcut(QKeySequence(Qt::Key_Escape), this);
    shortcutClose2.connect([this] { close(); });
}

void Window::setSize(int x, int y) {
    resize(x, y);
}

void Window::maximize() {
    QVector<int> dimensions = UtilityUI::getScreenBounds();
    resize(dimensions[0], dimensions[1]);
    // showMaximized();
}

void Window::setTitle(const QString& s) {
    setWindowTitle(s);
}
