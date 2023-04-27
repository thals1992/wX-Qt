// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCMCDWATCHMPDVIEWER_H
#define SPCMCDWATCHMPDVIEWER_H

#include <string>
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/Photo.h"
#include "ui/TwoWidgetScroll.h"
#include "ui/Shortcut.h"
#include "ui/Text.h"
#include "ui/Window.h"

using std::string;

class SpcMcdWatchMpdViewer : public Window {
public:
    SpcMcdWatchMpdViewer(QWidget *, const string&);

private:
    void updateText(const string&);
    static string getToken(const string&);
    QWidget * parent;
    VBox boxText;
    Text text;
    Photo photo;
    TwoWidgetScroll sw;
    Button button;
    Shortcut shortcut;
    string token;
};

#endif  // SPCMCDWATCHMPDVIEWER_H
