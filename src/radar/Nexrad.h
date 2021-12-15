// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NEXRAD_H
#define NEXRAD_H

#include "objects/ObjectAnimateNexrad.h"
#include "objects/Timer.h"
#include "radar/NexradWidget.h"
#include "radar/NexradLayerDownload.h"
#include "ui/Button.h"
#include "ui/ButtonToggle.h"
#include "ui/HBox.h"
#include "ui/RadarStatusBox.h"
#include "ui/StatusBar.h"
#include "ui/Window.h"
#include "ui/VBox.h"

class Nexrad : public Window {
public:
    Nexrad(QWidget *, int, bool, const QString&, bool);
    ~Nexrad();
    StatusBar statusBar;
    QVector<RadarStatusBox *> radarStatusBoxList;
    ObjectAnimateNexrad * objectAnimateNexrad;

protected:
    void closeEvent(QCloseEvent *) override;

private slots:
    void autoUpdate();
    void reload();
    void zoomInClicked();
    void zoomOutClicked();
    void moveLeftClicked();
    void moveRightClicked();
    void moveUpClicked();
    void moveDownClicked();
    void changeProduct();
    void changeSector();

private:
    void setupDropDowns();
    void setupToolbar();
    void setupBoxLayout();
    void setupShortCuts();
    void downloadData();
    void updateTitleForAutoRefresh();
    void writePreferences();
    void changeTilt();
    void changeZoom(double, int);
    void updateDrag(int);
    void changeProductForPane(int, const QString&);
    void changeSectorBySite(int, const QString&);
    void updateStatusBar();
    void settingsCheck();
    bool savePrefs;
    double movementSize = 100.0;
    VBox box;
    HBox radarLayout;
    HBox radarLayout2;
    HBox toolbarLayout;
    Button settingsButton;
    ButtonToggle animateButton;
    ComboBox comboboxAnimCount;
    ComboBox comboboxSector;
    ComboBox comboboxProduct;
    ComboBox comboboxTilt;
    ComboBox comboboxAnimSpeed;
    ButtonToggle reloadButton;
    Button moveLeft;
    Button moveRight;
    Button moveDown;
    Button moveUp;
    Button zoomOut;
    Button zoomIn;
    Shortcut shortcutReload;
    Shortcut shortAnimate;
    Shortcut shortcutZoomOut;
    Shortcut shortcutZoomIn;
    Shortcut shortcutMoveLeft;
    Shortcut shortcutMoveRight;
    Shortcut shortcutMoveUp;
    Shortcut shortcutMoveDown;
    Shortcut shortcutSettings;
    Shortcut shortcutU;
    Shortcut shortcutQ;
    Shortcut shortcutT;
    Shortcut shortcutL;
    Shortcut shortcutC;
    Shortcut shortcutKeyboard;
    bool useASpecificRadar;
    QString radarSite;
    QVector<NexradWidget *> nexradList;
    int radarIndex = 0;
    int numberOfPanes;
    Timer * reloadTimer;
    Text textFrameCount;
    Text textTilt;
    Text textAnimSpeed;
    NexradLayerDownload * nexradLayerDownload;
};

#endif  // NEXRAD_H
