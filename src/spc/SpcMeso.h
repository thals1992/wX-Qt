// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SPCMESO_H
#define SPCMESO_H

#include <QCloseEvent>
#include "objects/ObjectAnimate.h"
#include "ui/Button.h"
#include "ui/ButtonToggle.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/PopoverMenu.h"
#include "ui/Shortcut.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class SpcMeso : public Window {
public:
    explicit SpcMeso(QWidget *);

protected:
    void closeEvent(QCloseEvent *) override;

private:
    void reload();
    void changeProductForFav(int);
    void changeProductByCode(const QString& label);
    void changeSector();
    QString getUrl();
    void moveLeftClicked();
    void moveRightClicked();
    ObjectAnimate * objectAnimate;
    QString url;
    Photo photo;
    ButtonToggle animateButton;
    Button buttonBack;
    Button buttonForward;
    const QString prefTokenProduct = "SPCMESO1_PARAM_LAST_USED";
    const QString prefTokenSector = "SPCMESO1_SECTOR_LAST_USED";
    QVector<Button> buttons;
    ComboBox comboboxSector;
    HBox boxH;
    HBox imageLayout;
    VBox boxFav;
    VBox box;
    int index;
    int indexSector;
    QVector<PopoverMenu> popoverMenus;
    Shortcut shortcutAnimate;
    Shortcut shortcutLeft;
    Shortcut shortcutRight;
};

#endif  // SPCMESO_H
