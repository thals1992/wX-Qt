// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <unordered_map>
#include <vector>
#include "misc/SevereNotice.h"
#include "radar/NexradWidget.h"
#include "settings/UIPreferences.h"
#include "ui/CardHazards.h"
#include "ui/CardCurrentConditions.h"
#include "ui/SevenDayCollection.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/Image.h"
#include "ui/Toolbar.h"
#include "ui/ScrolledWindow.h"
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Window.h"
#include "util/CurrentConditions.h"
#include "util/Hazards.h"
#include "util/SevenDay.h"

using std::string;
using std::unordered_map;
using std::vector;

class MainWindow : public Window {
public:
    explicit MainWindow(QWidget * = nullptr);
    void reload();

protected:
    void closeEvent(QCloseEvent *) override;

private:
    void getCc();
    void updateCc();
    void update7day();
    void get7day();
    void updateHazards();
    void getHazards();
    void configChangeCheck();
    static string computeTokenString();
    void addWidgets();
    void locationChange();
    void launchImageScreen(const string&);
    HBox box;
    VBox vbox;
    VBox imageLayout;
    VBox rightMostLayout;
    VBox forecastLayout;
    VBox boxCc;
    VBox boxSevenDay;
    VBox boxHazards;
    ScrolledWindow sw;
    ComboBox comboBox;
    Toolbar objectToolbar;
    CurrentConditions currentConditions;
    Hazards hazards;
    SevenDay sevenDay;
    bool initializedCc{false};
    bool initialized7Day{false};
    CardCurrentConditions cardCurrentConditions;
    CardHazards cardHazards;
    SevenDayCollection sevenDayCollection;
    int imageIndex{};
    Shortcut shortcutClose;
    Shortcut shortcutVis;
    Shortcut shortcutWfoText;
    Shortcut shortcutHourly;
    Shortcut shortcutRadar;
    Shortcut shortcutRadarSinglePane;
    Shortcut shortcutRadarDualPane;
    Shortcut shortcutRadarQuadPane;
    Shortcut shortcutSevereDash;
    Shortcut shortcutNcep;
    Shortcut shortRadarMosaic;
    Shortcut shortcutNhc;
    Shortcut shortcutSettings;
    Shortcut shortcutSwo;
    Shortcut shortcutNationalImages;
    Shortcut shortcutSpcMeso;
    Shortcut shortcutSpcFire;
    Shortcut shortcutLightning;
    Shortcut shortcutReload;
    Shortcut shortcutKeyboard;
    Shortcut shortcutWpcText;
    Shortcut shortcutRtma;

    unordered_map<string, Image> imageWidgets;
    unordered_map<string, Text> textWidgets;
    string tokenString;
    int imageSize{UIPreferences::mainScreenImageSize};
    //
    // Mini SevereDashboard
    //
    void downloadWatch();
    void updateWatch();
    bool launch(int);
    HBox boxSevereDashboard;
    vector<string> urls;
    vector<Image> images;
    unordered_map<PolygonType, SevereNotice> watchesByType;
    vector<QByteArray> bytesList;
    //
    // Nexrad widget
    //
    vector<NexradWidget *> nexradList;
};

#endif  // MAINWINDOW_H
