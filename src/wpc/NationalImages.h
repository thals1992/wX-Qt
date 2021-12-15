// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WPCNATIONALIMAGES_H
#define WPCNATIONALIMAGES_H

#include "ui/Button.h"
#include "ui/HBox.h"
#include "ui/Photo.h"
#include "ui/PopoverMenu.h"
#include "ui/Shortcut.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class NationalImages : public Window {
public:
    explicit NationalImages(QWidget *);

private:
    void reload();
    void changeProductByCode(const QString&);
    void moveLeftClicked();
    void moveRightClicked();
    const QString prefToken = "WPCIMG_PARAM_LAST_USED";
    QString product;
    VBox box;
    HBox hbox;
    QVector<PopoverMenu> popoverMenus;
    Photo photo;
    int index;
    QString url;
    Button buttonBack;
    Button buttonForward;
    Shortcut shortcutLeft;
    Shortcut shortcutRight;
};

#endif  // WPCNATIONALIMAGES_H
