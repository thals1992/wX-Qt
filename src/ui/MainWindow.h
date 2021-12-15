// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "misc/SevereNotice.h"
#include "radar/NexradWidget.h"
#include "settings/UIPreferences.h"
#include "ui/ObjectCardHazards.h"
#include "ui/ObjectCardCurrentConditions.h"
#include "ui/ObjectCardSevenDay.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/Image.h"
#include "ui/ObjectToolbar.h"
#include "ui/ScrolledWindow.h"
#include "ui/Text.h"
#include "ui/VBox.h"
#include "ui/Window.h"
#include "util/ObjectCurrentConditions.h"
#include "util/ObjectHazards.h"
#include "util/ObjectSevenDay.h"

class MainWindow : public Window {
public:
    explicit MainWindow(QWidget * parent = nullptr);
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
    QString computeTokenString();
    void addWidgets();
    void locationChange();
    void launchImageScreen(QString);
    ObjectToolbar * objectToolbar;
    ObjectCurrentConditions objectCurrentConditions;
    ObjectHazards objectHazards;
    ObjectSevenDay objectSevenDay;
    bool initializedCc = false;
    bool initialized7Day = false;
    ScrolledWindow sw;
    VBox forecastLayout;
    VBox boxCc;
    VBox boxSevenDay;
    VBox boxHazards;
    ObjectCardCurrentConditions objectCardCurrentConditions;
    ObjectCardHazards * objectCardHazards;
    ObjectCardSevenDay objectCardSevenDay;
    ComboBox comboBox;
    int imageIndex;
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
    HBox box;
    VBox vbox;
    VBox imageLayout;
    VBox rightMostLayout;
    bool showImage;
    QHash<QString, Image> imageWidgets;
    QHash<QString, Text> textWidgets;
    QHash<QString, QByteArray> byteArrays;
    QHash<QString, QString> htmlMap;
    QString tokenString;
    int imageSize = UIPreferences::mainScreenImageSize;
    //
    // Mini SevereDashboard
    //
    void downloadWatch();
    void updateWatch();
    bool launch(int);
    HBox boxSevereDashboard;
    QStringList urls;
    QVector<Image> images;
    QHash<PolygonType, SevereNotice> watchesByType;
    QVector<QByteArray> bytesList;
    //
    // Nexrad widget
    //
    QVector<NexradWidget *> nexradList;
};

#endif  // MAINWINDOW_H
