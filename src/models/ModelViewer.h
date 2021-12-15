// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef MODELVIEWER_H
#define MODELVIEWER_H

#include "models/ObjectModel.h"
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/Photo.h"
#include "ui/VBox.h"
#include "ui/Window.h"

class ModelViewer : public Window {
public:
    ModelViewer(QWidget *, const QString&);

private:
    void changeModelCb();
    void changeRunCb();
    void changeSectorCb();
    void changeProductCb();
    void changeTimeCb();
    void changeModel(int);
    void changeParam(int);
    void changeSector(int);
    void changeRun(int);
    void changeTime(int);
    void moveLeftClicked();
    void moveRightClicked();
    void reload();
    void getRun();
    void getRunStatus();
    void updateRunStatus();
    QString modelType;
    ObjectModel modelObj;
    ComboBox comboboxTime;
    ComboBox comboboxModel;
    ComboBox comboboxRun;
    ComboBox comboboxProduct;
    ComboBox comboboxSector;
    Button leftButton;
    Button rightButton;
    HBox boxH;
    VBox box;
    Photo photo;
};

#endif  // MODELVIEWER_H
