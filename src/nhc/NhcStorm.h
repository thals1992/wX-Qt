// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NHCSTORM_H
#define NHCSTORM_H

#include "nhc/ObjectNhcStormDetails.h"
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/ObjectTwoWidgetScroll.h"
#include "ui/Photo.h"
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class NhcStorm : public Window {
public:
    NhcStorm(QWidget *, const ObjectNhcStormDetails&);

private:
    void reload();
    void changeProduct();
    void launchGoes();
    ObjectNhcStormDetails stormData;
    QWidget * parent;
    VBox boxText;
    VBox boxImages;
    VBox box;
    VBox imageVBox;
    QVector<HBox> boxRows;
    QVector<Photo> images;
    QStringList urls;
    QString product;
    Text text;
    ComboBox comboboxProduct;
    HBox boxRow;
    ObjectTwoWidgetScroll sw;
    Button goesButton;
    QString goesUrl;
};

#endif  // NHCSTORM_H
