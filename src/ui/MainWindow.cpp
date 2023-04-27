// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "MainWindow.h"
#include "common/GlobalVariables.h"
#include "objects/FutureText.h"
#include "objects/FutureVoid.h"
#include "objects/PolygonWatch.h"
#include "misc/TextViewerStatic.h"
#include "misc/UsAlerts.h"
#include "spc/SpcMcdWatchMpdViewer.h"
#include "spc/SpcStormReports.h"
#include "settings/Location.h"
#include "util/DownloadImage.h"
#include "util/UtilityIO.h"
#include "util/UtilityList.h"
#include "util/UtilityUI.h"

MainWindow::MainWindow(QWidget * parent)
    : Window{parent}
    , sw{ ScrolledWindow{this, vbox} }
    , comboBox{ ComboBox{this, Location::listOfNames()} }
    , objectToolbar{ Toolbar{this, [this] { reload(); }} }
    , shortcutClose{ Shortcut{QKeySequence{"Q"}, this} }
    , shortcutVis{ Shortcut{QKeySequence{"C"}, this} }  // was QKeySequence("Ctrl+C")
    , shortcutWfoText{ Shortcut{QKeySequence{"A"}, this} }
    , shortcutHourly{ Shortcut{QKeySequence{"H"}, this} }
    , shortcutRadar{ Shortcut{QKeySequence{"R"}, this} }
    , shortcutRadarSinglePane{ Shortcut{QKeySequence{"1"}, this} }
    , shortcutRadarDualPane{ Shortcut{QKeySequence{"2"}, this} }
    , shortcutRadarQuadPane{ Shortcut{QKeySequence{"4"}, this} }
    , shortcutSevereDash{ Shortcut{QKeySequence{"D"}, this} }
    , shortcutNcep{ Shortcut{QKeySequence{"N"}, this} }
    , shortRadarMosaic{ Shortcut{QKeySequence{"M"}, this} }
    , shortcutNhc{ Shortcut{QKeySequence{"O"}, this} }
    , shortcutSettings{ Shortcut{QKeySequence{"P"}, this} }
    , shortcutSwo{ Shortcut{QKeySequence{"S"}, this} }
    , shortcutNationalImages{ Shortcut{QKeySequence{"I"}, this} }
    , shortcutSpcMeso{ Shortcut{QKeySequence{"Z"}, this} }
    , shortcutSpcFire{ Shortcut{QKeySequence{"F"}, this} }
    , shortcutLightning{ Shortcut{QKeySequence{"L"}, this} }
    , shortcutReload{ Shortcut{QKeySequence{"U"}, this} }
    , shortcutKeyboard{ Shortcut{QKeySequence{"/"}, this} }
    , shortcutWpcText{ Shortcut{QKeySequence{"T"}, this} }
    , shortcutRtma{ Shortcut{QKeySequence{"B"}, this} }
{
    setTitle(GlobalVariables::appName);
    watchesByType.insert({Watch, SevereNotice{Watch}});
    watchesByType.insert({Mcd, SevereNotice{Mcd}});
    watchesByType.insert({Mpd, SevereNotice{Mpd}});

    comboBox.setIndex(Location::currentLocationIndex);
    comboBox.connect([this] { locationChange(); });
    Location::comboBox = &comboBox;
    //
    // TEST init nexrad
    //
    if (UIPreferences::nexradMainScreen) {
        auto sb = new StatusBar{this};
        nexradList.push_back(
            new NexradWidget{
                this,
                *sb,
                0,
                1,
                true,
                Location::radarSite(),
                UIPreferences::mainScreenImageSize,
                UIPreferences::mainScreenImageSize,
                [] ([[maybe_unused]] int pane, [[maybe_unused]] const string& prod) {},
                [] ([[maybe_unused]] int pane, [[maybe_unused]] const string& sector) {},
                [] ([[maybe_unused]] double z, [[maybe_unused]] int pane) {},
                [] ([[maybe_unused]] int pane) {}
            });
    }
    boxSevenDay.setSpacing(0);
    addWidgets();
    vbox.addLayout(boxSevereDashboard);
    vbox.addLayout(box);
    box.addLayout(objectToolbar);
    box.addLayout(imageLayout);
    box.addLayout(forecastLayout);
    box.addLayout(rightMostLayout);

    forecastLayout.addWidget(comboBox);
    forecastLayout.addLayout(boxCc);
    forecastLayout.addLayout(boxHazards);
    forecastLayout.addLayout(boxSevenDay);
    forecastLayout.addStretch();
    // QScroller::grabGesture(vbox.get(), QScroller::TouchGesture);
    shortcutClose.connect([this] { close(); });
    shortcutVis.connect([this] { objectToolbar.launchGoesViewer(); });
    shortcutWfoText.connect([this] { objectToolbar.launchWfoText(); });
    shortcutHourly.connect([this] { objectToolbar.launchHourly(); });
    shortcutRadar.connect([this] { objectToolbar.launchNexrad(1); });
    shortcutRadarSinglePane.connect([this] { objectToolbar.launchNexrad(1); });
    shortcutRadarDualPane.connect([this] { objectToolbar.launchNexrad(2); });
    shortcutRadarQuadPane.connect([this] { objectToolbar.launchNexrad(4); });
    shortcutSevereDash.connect([this] { objectToolbar.launchSevereDashboard(); });
    shortcutNcep.connect([this] { objectToolbar.launchModelViewerGeneric("NCEP"); });
    shortRadarMosaic.connect([this] { objectToolbar.launchRadarMosaicViewer(); });
    shortcutNhc.connect([this] { objectToolbar.launchNhc(); });
    shortcutSettings.connect([this] { objectToolbar.launchSettings(); });
    shortcutSwo.connect([this] { objectToolbar.launchSpcSwoSummary(); });
    shortcutNationalImages.connect([this] { objectToolbar.launchNationalImages(); });
    shortcutSpcMeso.connect([this] { objectToolbar.launchSpcMeso(); });
    shortcutSpcFire.connect([this] { objectToolbar.launchSpcFireWeatherOutlookSummary(); });
    shortcutLightning.connect([this] { objectToolbar.launchLightning(); });
    shortcutReload.connect([this] { reload(); });
    shortcutKeyboard.connect([this] { new TextViewerStatic{this, GlobalVariables::mainScreenShortcuts, 700, 600}; });
    shortcutWpcText.connect([this] { objectToolbar.launchNationalText(); });
    shortcutRtma.connect([this] { objectToolbar.launchRtma(); });

    reload();
}

void MainWindow::locationChange() {
    auto index = comboBox.getIndex();
    if (index == -1) {
        return;
    }
    Location::setCurrentLocation(index);
    reload();
}

void MainWindow::updateHazards() {
    cardHazards.removeLabels();
    cardHazards = CardHazards{this, hazards};
    boxHazards.addLayout(cardHazards);
}

void MainWindow::getHazards() {
    hazards.process(Location::getLatLonCurrent());
}

void MainWindow::update7day() {
    if (!initialized7Day || sevenDayCollection.sevenDayCard.empty()) {
        sevenDayCollection = SevenDayCollection{this, boxSevenDay, &sevenDay};
        initialized7Day = true;
    } else {
        sevenDayCollection.update();
    }
}

void MainWindow::get7day() {
    sevenDay.process(Location::getLatLonCurrent());
}

void MainWindow::updateCc() {
    if (!initializedCc) {
        cardCurrentConditions = CardCurrentConditions{this, currentConditions};
        boxCc.addLayout(cardCurrentConditions);
        initializedCc = true;
    } else {
        cardCurrentConditions.update(currentConditions);
    }
}

void MainWindow::getCc() {
    currentConditions.process(Location::getLatLonCurrent(), 0);
    currentConditions.timeCheck();
}

void MainWindow::reload() {
    configChangeCheck();
    new FutureVoid{this, [this] { getCc(); }, [this] { updateCc(); }};
    new FutureVoid{this, [this] { getHazards(); }, [this] { updateHazards(); }};
    new FutureVoid{this, [this] { get7day(); }, [this] { update7day(); }};

    for (const auto& item : UIPreferences::homeScreenItemsText) {
        if (item.isEnabled()) {
            const auto t = item.prefToken;
            new FutureText{this, item.prefToken, [this, t] (const auto& s) { textWidgets[t].setText(s); }};
        }
    }
    for (const auto& item : UIPreferences::homeScreenItemsImage) {
        if (item.isEnabled()) {
            const auto url = DownloadImage::byProduct(item.prefToken);
            const auto token = item.prefToken;
            new FutureBytes{this, url, [this, token] (const auto& ba) { imageWidgets[token].setToWidth(ba, UIPreferences::mainScreenImageSize); }};
        }
    }
    if (UIPreferences::nexradMainScreen) {
        auto pane = 0;
        nexradList[pane]->nexradState.setRadar(Location::radarSite());
        nexradList[pane]->nexradState.reset();
        nexradList[pane]->nexradState.zoom = 0.6;

//        nexradList[pane]->nexradDraw.initGeom();
//        nexradList[pane]->update();
//        // FIXME TODO crashes in downloadData FutureBytes
//         nexradList[pane]->downloadData();
    }
    if (UIPreferences::mainScreenSevereDashboard) {
        new FutureVoid{this, [this] { downloadWatch(); }, [this] { updateWatch(); }};
    } else {
        boxSevereDashboard.removeChildren();
    }
}

void MainWindow::downloadWatch() {
    urls.clear();
    for (auto type : {Mcd, Mpd, Watch}) {
        PolygonWatch::byType[type]->download();
    }
    urls.push_back(DownloadImage::byProduct("USWARN"));
    urls.push_back(DownloadImage::byProduct("STRPT"));
    for (auto type : {Watch, Mcd, Mpd}) {
        PolygonWatch::byType[type]->download();
        watchesByType.at(type).getBitmaps();
        addAll(urls, watchesByType.at(type).urls);
    }
    for (auto index : range(urls.size())) {
        bytesList.push_back(UtilityIO::downloadAsByteArray(urls[index]));
    }
}

void MainWindow::updateWatch() {
    boxSevereDashboard.removeChildren();
    images.clear();
    for ([[maybe_unused]] auto index : range(urls.size())) {
        images.emplace_back(this);
        images.back().imageSize = 150;
    }
    for (auto index : range(urls.size())) {
        images[index].setBytes(bytesList[index]);
        images[index].connect([this, index] { launch(index); });
        boxSevereDashboard.addWidget(images[index]);
    }
}

bool MainWindow::launch(int indexFinal) {
    if (indexFinal == 0) {
        new UsAlerts{this};
    } else if (indexFinal == 1) {
        new SpcStormReports{this, "today"};
    } else if (indexFinal > 1) {
        new SpcMcdWatchMpdViewer{this, urls[indexFinal]};
    }
    return true;
}

void MainWindow::configChangeCheck() {
    if (tokenString != computeTokenString() || UIPreferences::mainScreenImageSize != imageSize) {
        addWidgets();
    }
    objectToolbar.refresh();
}

void MainWindow::addWidgets() {
    imageLayout.removeChildren();
    rightMostLayout.removeChildren();
    imageWidgets.clear();
    textWidgets.clear();
    boxSevereDashboard.removeChildren();
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
    imageIndex = 0;
    for (const auto& item : UIPreferences::homeScreenItemsImage) {
        if (item.isEnabled()) {
            imageWidgets[item.prefToken] = Image{this};
            const auto tokenFinal = item.prefToken;
            imageWidgets[item.prefToken].connect([this, tokenFinal] { launchImageScreen(tokenFinal); });
            imageLayout.addWidget(imageWidgets[item.prefToken]);
        }
        imageSize = UIPreferences::mainScreenImageSize;
        imageIndex += 1;
    }
    if (imageIndex > 0) {
        imageLayout.addStretch();
    }
    //
    // Textual right sidebar (hourly)
    //
    for (const auto& item : UIPreferences::homeScreenItemsText) {
        if (item.isEnabled()) {
            textWidgets[item.prefToken] = Text{this};
            textWidgets[item.prefToken].setFixedWidth();
            rightMostLayout.addWidget(textWidgets[item.prefToken]);
        }
    }
}

string MainWindow::computeTokenString() {
    string ts;
    for (const auto& item : UIPreferences::homeScreenItemsImage) {
        if (item.isEnabled()) {
            ts += item.prefToken;
        }
    }
    for (const auto& item : UIPreferences::homeScreenItemsText) {
        if (item.isEnabled()) {
            ts += item.prefToken;
        }
    }
    return ts;
}

void MainWindow::closeEvent(QCloseEvent * event) {
    event->accept();
}

void MainWindow::launchImageScreen(const string& token) {
    if (token == "VISIBLE_SATELLITE") {
        objectToolbar.launchGoesViewer();
    } else if (token == "RADAR_MOSAIC") {
        objectToolbar.launchRadarMosaicViewer();
    } else if (token == "ANALYSIS_RADAR_AND_WARNINGS") {
        objectToolbar.launchNationalImages();
    } else if (token == "USWARN") {
        objectToolbar.launchUsAlerts();
    } else if (token == "RTMA_TEMP") {
        objectToolbar.launchRtma();
    }
}
