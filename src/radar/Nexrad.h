// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NEXRAD_H
#define NEXRAD_H

#include <memory>
#include <string>
#include <vector>
#include "objects/ObjectAnimateNexrad.h"
// #include <QGeoPositionInfo>
// #include <QGeoPositionInfoSource>
#include "objects/Timer.h"
#include "radar/NexradWidget.h"
#include "radar/NexradLayerDownload.h"
#include "ui/Button.h"
#include "ui/ButtonToggle.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/StatusBar.h"
#include "ui/Window.h"
#include "ui/VBox.h"

using std::string;
using std::vector;

class Nexrad : public Window {
public:
    Nexrad(QWidget *, int, bool, const string&);
    ~Nexrad() override;

protected:
    void closeEvent(QCloseEvent *) override;

private slots:
    void autoUpdate();
    void toggleAutoUpdate();
    void changePosition(double, double);
    void changeProduct();

private:
    void setupDropDowns();
    void setupToolbar();
    void setupBoxLayout();
    void setupShortCuts();
    void syncRadarSite(const string&, int);
    void downloadData();
    void updateTitleForAutoRefresh();
    void changeTilt();
    void changeZoom(double, int);
    void updateDrag(int);
    void settingsCheck();
    void changeProductFromChild(const string&, int);
    void changeRadarSite();
    void changeSectorFromChild(const string&, int);
    // void positionUpdated(const QGeoPositionInfo&);
    // QGeoPositionInfoSource * source;
    VBox box;
    HBox radarLayout;
    HBox radarLayout2;
    HBox toolbarLayout;
    int numberOfPanes;
    StatusBar statusBar;
    Timer reloadTimer;
    ComboBox comboboxSector;
    ComboBox comboboxProduct;
    ComboBox comboboxTilt;
    ComboBox comboboxAnimCount;
    ComboBox comboboxAnimSpeed;
    ButtonToggle animateButton;
    ButtonToggle reloadButton;
    Button settingsButton;
    Button moveLeftButton;
    Button moveRightButton;
    Button moveDownButton;
    Button moveUpButton;
    Button zoomOutButton;
    Button zoomInButton;
    vector<NexradWidget *> nexradList;
    Text textFrameCount;
    Text textTilt;
    Text textAnimSpeed;
    NexradLayerDownload nexradLayerDownload;
    ObjectAnimateNexrad objectAnimateNexrad;
    Shortcut shortcutReload;
    Shortcut shortcutU;
    Shortcut shortcutQ;
    Shortcut shortcutL;
    Shortcut shortcutT;
    Shortcut shortcutC;
    Shortcut shortAnimate;
    Shortcut shortcutZoomIn;
    Shortcut shortcutZoomOut;
    Shortcut shortcutMoveLeft;
    Shortcut shortcutMoveRight;
    Shortcut shortcutMoveUp;
    Shortcut shortcutMoveDown;
    Shortcut shortcutKeyboard;
    Shortcut shortcutSettings;
    double moveIncrement{100.0};
};

#endif  // NEXRAD_H
