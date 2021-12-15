// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "MainWindow.h"
#include "common/GlobalVariables.h"
#include "objects/FutureText.h"
#include "objects/FutureBytes.h"
#include "objects/FutureVoid.h"
#include "objects/ObjectPolygonWatch.h"
#include "misc/TextViewerStatic.h"
#include "misc/UsAlerts.h"
#include "radar/Nexrad.h"
#include "spc/SpcMcdWatchMpdViewer.h"
#include "spc/SpcStormReports.h"
#include "settings/Location.h"
#include "util/UtilityDownload.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityUI.h"

MainWindow::MainWindow(QWidget * parent) : Window(parent) {
    setTitle(GlobalVariables::appName);
    auto dimensions = UtilityUI::getScreenBounds();
    resize(dimensions[0], dimensions[1]);
    // maximize();

    watchesByType[PolygonType::watch] = SevereNotice(PolygonType::watch);
    watchesByType[PolygonType::mcd] = SevereNotice(PolygonType::mcd);
    watchesByType[PolygonType::mpd] = SevereNotice(PolygonType::mpd);

    //
    // TEST init nexrad
    //
    if (UIPreferences::nexradMainScreen) {
        StatusBar * sb = new StatusBar(this);
        RadarStatusBox * rsb = new RadarStatusBox(this);
        nexradList.push_back(
            new NexradWidget(
                this, 
                *sb,
                rsb,
                0,
                1,
                true,
                Location::radarSite(),
                UIPreferences::mainScreenImageSize,
                UIPreferences::mainScreenImageSize,
                UIPreferences::mainScreenImageSize,
                UIPreferences::mainScreenImageSize,
                [] ([[maybe_unused]] int pane, [[maybe_unused]] QString prod) {},
                [] ([[maybe_unused]] int pane, [[maybe_unused]] QString sector) {},
                [] ([[maybe_unused]] double z, [[maybe_unused]] int pane) {},
                [] ([[maybe_unused]] int pane) {}
                )
            );
    }

    box = HBox(this);
    vbox = VBox(this);
    boxSevereDashboard = HBox(this);
    imageLayout = VBox(this);
    rightMostLayout = VBox(this);

    forecastLayout = VBox(this);
    boxCc = VBox(this);
    boxSevenDay = VBox(this);
    boxSevenDay.setSpacing(0);
    boxHazards = VBox(this);
    objectCardHazards = new ObjectCardHazards();

    comboBox = ComboBox(this, Location::listOfNames());
    comboBox.setIndex(Location::currentLocationIndex);
    comboBox.connect([this] { locationChange(); });

    //
    // setup toolbar
    //
    objectToolbar = new ObjectToolbar(this, [this] { reload(); }, &comboBox);
    addWidgets();

    if (UIPreferences::mainScreenSevereDashboard) {
        vbox.addLayout(boxSevereDashboard.get());
    }
    vbox.addLayout(box.get());
    box.addLayout(objectToolbar->get());
    box.addLayout(imageLayout.get());
    box.addLayout(forecastLayout.get());
    box.addLayout(rightMostLayout.get());

    forecastLayout.addWidget(comboBox.get());
    forecastLayout.addLayout(boxCc.get());
    forecastLayout.addLayout(boxHazards.get());
    forecastLayout.addLayout(boxSevenDay.get());
    forecastLayout.addStretch();
    sw = ScrolledWindow(this, vbox.get());

    shortcutClose = Shortcut(QKeySequence("Ctrl+Q"), this);
    shortcutClose.connect([this] { close(); });

    shortcutVis = Shortcut(QKeySequence("Ctrl+C"), this);
    shortcutVis.connect([this] { objectToolbar->launchGoesViewer(); });

    shortcutWfoText = Shortcut(QKeySequence("Ctrl+A"), this);
    shortcutWfoText.connect([this] { objectToolbar->launchWfoText(); });

    shortcutHourly = Shortcut(QKeySequence("Ctrl+H"), this);
    shortcutHourly.connect([this] { objectToolbar->launchHourly(); });

    shortcutRadar = Shortcut(QKeySequence("Ctrl+R"), this);
    shortcutRadar.connect([this] { objectToolbar->launchNexrad(1); });

    shortcutRadarSinglePane = Shortcut(QKeySequence("Ctrl+1"), this);
    shortcutRadarSinglePane.connect([this] { objectToolbar->launchNexrad(1); });

    shortcutRadarDualPane = Shortcut(QKeySequence("Ctrl+2"), this);
    shortcutRadarDualPane.connect([this] { objectToolbar->launchNexrad(2); });

    shortcutRadarQuadPane = Shortcut(QKeySequence("Ctrl+4"), this);
    shortcutRadarQuadPane.connect([this] { objectToolbar->launchNexrad(4); });

    shortcutSevereDash = Shortcut(QKeySequence("Ctrl+D"), this);
    shortcutSevereDash.connect([this] { objectToolbar->launchSevereDashboard(); });

    shortcutNcep = Shortcut(QKeySequence("Ctrl+N"), this);
    shortcutNcep.connect([this] { objectToolbar->launchModelViewerGeneric("NCEP"); });

    shortRadarMosaic = Shortcut(QKeySequence("Ctrl+M"), this);
    shortRadarMosaic.connect([this] { objectToolbar->launchRadarMosaicViewer(); });

    shortcutNhc = Shortcut(QKeySequence("Ctrl+O"), this);
    shortcutNhc.connect([this] { objectToolbar->launchNhc(); });

    shortcutSettings = Shortcut(QKeySequence("Ctrl+P"), this);
    shortcutSettings.connect([this] { objectToolbar->launchSettings(); });

    shortcutSwo = Shortcut(QKeySequence("Ctrl+S"), this);
    shortcutSwo.connect([this] { objectToolbar->launchSpcSwoSummary(); });

    shortcutNationalImages = Shortcut(QKeySequence("Ctrl+I"), this);
    shortcutNationalImages.connect([this] { objectToolbar->launchNationalImages(); });

    shortcutSpcMeso = Shortcut(QKeySequence("Ctrl+Z"), this);
    shortcutSpcMeso.connect([this] { objectToolbar->launchSpcMeso(); });

    shortcutSpcFire = Shortcut(QKeySequence("Ctrl+F"), this);
    shortcutSpcFire.connect([this] { objectToolbar->launchSpcFireWeatherOutlookSummary(); });

    shortcutLightning = Shortcut(QKeySequence("Ctrl+L"), this);
    shortcutLightning.connect([this] { objectToolbar->launchLightning(); });

    shortcutReload = Shortcut(QKeySequence("Ctrl+U"), this);
    shortcutReload.connect([this] { reload(); });

    shortcutKeyboard = Shortcut(QKeySequence("Ctrl+/"), this);
    shortcutKeyboard.connect([this] { new TextViewerStatic(this, GlobalVariables::mainScreenShortcuts, 700, 600); });

    shortcutWpcText = Shortcut(QKeySequence("Ctrl+T"), this);
    shortcutWpcText.connect([this] { objectToolbar->launchNationalText(); });

    reload();
}

void MainWindow::locationChange() {
    auto index = comboBox.getIndex();
    if (index == -1) {
        return;
    }
    Location::changeLocationByIndex(index);
    reload();
}

void MainWindow::updateHazards() {
    objectCardHazards->removeLabels();
    objectCardHazards = new ObjectCardHazards(this, objectHazards);
    boxHazards.addLayout(objectCardHazards->get());
}

void MainWindow::getHazards() {
    objectHazards = ObjectHazards(Location::getLatLonCurrent());
}

void MainWindow::update7day() {
    if (!initialized7Day || objectCardSevenDay.cards.size() == 0) {
        objectCardSevenDay = ObjectCardSevenDay(this, boxSevenDay, objectSevenDay.detailedForecasts, objectSevenDay.icons);
        initialized7Day = true;
    } else {
        objectCardSevenDay.update(objectSevenDay.detailedForecasts, objectSevenDay.icons);
    }
}

void MainWindow::get7day() {
    objectSevenDay = ObjectSevenDay(Location::getLatLonCurrent());
    objectSevenDay.process();
}

void MainWindow::updateCc() {
    if (!initializedCc) {
        objectCardCurrentConditions = ObjectCardCurrentConditions(this, objectCurrentConditions);
        boxCc.addLayout(objectCardCurrentConditions.get());
        initializedCc = true;
    } else {
        objectCardCurrentConditions.update(objectCurrentConditions);
    }
}

void MainWindow::getCc() {
    objectCurrentConditions = ObjectCurrentConditions(Location::getLatLonCurrent());
    objectCurrentConditions.process();
}

void MainWindow::reload() {
    configChangeCheck();
    new FutureVoid(this, [this] { getCc(); }, [this] { updateCc(); });
    new FutureVoid(this, [this] { getHazards(); }, [this] { updateHazards(); });
    new FutureVoid(this, [this] { get7day(); }, [this] { update7day(); });

    for (const auto& item : UIPreferences::homeScreenItemsText) {
        if (item.isEnabled()) {
            const auto t = item.prefToken;
            new FutureText(this, item.prefToken, [this, t] (const auto& s) { textWidgets[t].setText(s); });
        }
    }
    for (const auto& item : UIPreferences::homeScreenItemsImage) {
        if (item.isEnabled()) {
            auto url = UtilityDownload::getImageProduct(item.prefToken);
            const auto token = item.prefToken;
            new FutureBytes(this, url, [this, token] (const auto& ba) { imageWidgets[token].setToWidth(ba, UIPreferences::mainScreenImageSize); });
        }
    }
    if (UIPreferences::nexradMainScreen) {
        auto pane = 0;
        nexradList[pane]->nexradState.radarSite = Location::radarSite();
        nexradList[pane]->nexradState.reset();
        nexradList[pane]->nexradState.zoom = 0.6;

        nexradList[pane]->initializeGeom();
        nexradList[pane]->update();
        // FIXME TODO crashes in downloadData FutureBytes
        // nexradList[pane]->downloadData();
    }
    if (UIPreferences::mainScreenSevereDashboard) {
        new FutureVoid(this, [this] { downloadWatch(); }, [this] { updateWatch(); });
    }
}

void MainWindow::downloadWatch() {
    urls.clear();
    for (auto t : {PolygonType::mcd, PolygonType::mpd, PolygonType::watch}) {
        ObjectPolygonWatch::polygonDataByType[t]->download();
    }
    urls.push_back(UtilityDownload::getImageProduct("USWARN"));
    urls.push_back(UtilityDownload::getImageProduct("STRPT"));
    for (auto t : {PolygonType::watch, PolygonType::mcd, PolygonType::mpd}) {
        ObjectPolygonWatch::polygonDataByType[t]->download();
        watchesByType[t].getBitmaps();
        urls.append(watchesByType[t].urls);
    }
    for (auto index : UtilityList::range(urls.size())) {
        bytesList.push_back(UtilityIO::downloadAsByteArray(urls[index]));
    }
}

void MainWindow::updateWatch() {
    for (auto index : UtilityList::range(urls.size())) {
        images.push_back(Image::withIndex(this, index));
        images.back().imageSize = 150;
    }
    for (auto index : UtilityList::range(urls.size())) {
        images[index].setBytes(bytesList[index]);
        images[index].connect([this, index] { launch(index); });
        boxSevereDashboard.addWidget(images[index].get());
    }
}

bool MainWindow::launch(int indexFinal) {
    if (indexFinal == 0) {
        new UsAlerts(this);
    } else if (indexFinal == 1) {
        new SpcStormReports(this, "today");
    } else if (indexFinal > 1) {
        new SpcMcdWatchMpdViewer(this, urls[indexFinal]);
    }
    return true;
}

void MainWindow::configChangeCheck() {
    if (tokenString != computeTokenString() || UIPreferences::mainScreenImageSize != imageSize) {
        addWidgets();
    }
}

void MainWindow::addWidgets() {
    imageLayout.removeChildren();
    rightMostLayout.removeChildren();
    imageWidgets.clear();
    textWidgets.clear();
    if (UIPreferences::mainScreenSevereDashboard) {
        boxSevereDashboard.removeChildren();
    }
    //
    // TEST - put nexrad at top
    //
    if (UIPreferences::nexradMainScreen) {
        nexradList[0]->setFixedHeight(UIPreferences::mainScreenImageSize);
        nexradList[0]->setFixedWidth(UIPreferences::mainScreenImageSize);
        imageLayout.addWidget(nexradList[0]);
    }
    //
    // image setup
    //
    showImage = false;
    imageIndex = 0;
    for (const auto& item : UIPreferences::homeScreenItemsImage) {
        if (item.isEnabled()) {
            imageWidgets[item.prefToken] = Image(this);
            const auto tokenFinal = item.prefToken;
            imageWidgets[item.prefToken].connect([this, tokenFinal] { launchImageScreen(tokenFinal); });
            imageLayout.addWidget(imageWidgets[item.prefToken].get());
            showImage = true;
        }
        imageSize = UIPreferences::mainScreenImageSize;
        imageIndex += 1;
    }
    if (imageIndex > 0) {
        imageLayout.addStretch();
    }
    //
    // Textual right side bar (hourly)
    //
    for (const auto& item : UIPreferences::homeScreenItemsText) {
        if (item.isEnabled()) {
            textWidgets[item.prefToken] = Text(this, "");
            textWidgets[item.prefToken].setFixedWidth();
            rightMostLayout.addWidget(textWidgets[item.prefToken].get());
        }
    }
}

QString MainWindow::computeTokenString() {
    QString tokenString = "";
    for (const auto& item : UIPreferences::homeScreenItemsImage) {
        if (item.isEnabled()) {
            tokenString += item.prefToken;
        }
    }
    for (const auto& item : UIPreferences::homeScreenItemsText) {
        if (item.isEnabled()) {
            tokenString += item.prefToken;
        }
    }
    return tokenString;
}

void MainWindow::closeEvent(QCloseEvent * event) {
    event->accept();
}

void MainWindow::launchImageScreen(QString token) {
    if (token == "VISIBLE_SATELLITE") {
        objectToolbar->launchGoesViewer();
    } else if (token == "RADAR_MOSAIC") {
        objectToolbar->launchRadarMosaicViewer();
    } else if (token == "ANALYSIS_RADAR_AND_WARNINGS") {
        objectToolbar->launchNationalImages();
    } else if (token == "USWARN") {
        objectToolbar->launchUsAlerts();
    }
}
