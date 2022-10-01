// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCLSRBYWFO_H
#define SPCLSRBYWFO_H

#include <string>
#include <vector>
#include "ui/ComboBox.h"
#include "ui/ScrolledWindow.h"
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Window.h"

using std::string;
using std::vector;

class LsrByWfo : public Window {
public:
    explicit LsrByWfo(QWidget *);

private:
    void changeSector();
    void getLsrFromWfo();
    void reload();
    void download(int, int);
    void update(int);
    VBox box;
    VBox boxText;
    ScrolledWindow sw;
    ComboBox comboboxSector;
    string wfo;
    vector<string> lsrList;
    vector<Text> textList;
};

#endif  // SPCLSRBYWFO_H
