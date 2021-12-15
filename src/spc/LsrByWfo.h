// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCLSRBYWFO_H
#define SPCLSRBYWFO_H

#include "ui/ComboBox.h"
#include "ui/ScrolledWindow.h"
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class LsrByWfo : public Window {
public:
    LsrByWfo(QWidget *);

private:
    void changeSector();
    void getLsrFromWfo();
    void reload();
    void download(int, int);
    void update(int);
    VBox box;
    VBox boxText;
    QStringList lsrList;
    QVector<Text> textList;
    QString wfo;
    ComboBox comboboxSector;
    ScrolledWindow sw;
};

#endif  // SPCLSRBYWFO_H
