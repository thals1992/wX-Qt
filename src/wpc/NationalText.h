// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WPCNATIONALTEXT_H
#define WPCNATIONALTEXT_H

#include "ui/Button.h"
#include "ui/PopoverMenu.h"
#include "ui/Shortcut.h"
#include "ui/Text.h"
#include "ui/Window.h"
#include "ui/ScrolledWindow.h"
#include "ui/VBox.h"

class NationalText : public Window {
public:
    explicit NationalText(QWidget *, const QString& = "");

private:
    void reload();
    void changeProductByCode(const QString&);
    void moveLeftClicked();
    void moveRightClicked();
    QString product = "PMDSPD";
    int index;
    const QString prefTokenProduct = "WPCTEXT_PARAM_LAST_USED";
    Text text;
    VBox box;
    HBox hbox;
    QVector<PopoverMenu> popoverMenus;
    ScrolledWindow sw;
    bool savePref = true;
    Button buttonBack;
    Button buttonForward;
    Shortcut shortcutLeft;
    Shortcut shortcutRight;
};

#endif  // WPCNATIONALTEXT_H
