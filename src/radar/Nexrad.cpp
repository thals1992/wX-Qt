// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/Nexrad.h"
#include <QKeySequence>
#include <algorithm>
#include <cmath>
#include "common/GlobalArrays.h"
#include "common/GlobalVariables.h"
#include "objects/WString.h"
#include "misc/TextViewerStatic.h"
#include "objects/ObjectDateTime.h"
#include "radar/NexradUtil.h"
#include "radar/RadarGeometry.h"
#include "settings/RadarPreferences.h"
#include "settings/SettingsMain.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityList.h"
#include "util/UtilityLog.h"
#include "util/UtilityUI.h"

Nexrad::Nexrad(QWidget * parent, int numberOfPanes, bool useASpecificRadar, const string& radarSite)
    : Window{parent}
    , numberOfPanes{ numberOfPanes }
    , statusBar{ StatusBar{this} }
    , reloadTimer{ Timer{this, [this] { autoUpdate(); }} }
    , comboboxSector{ ComboBox{this, GlobalArrays::radars()} }
    , comboboxProduct{ ComboBox{this, NexradUtil::radarProductList} }
    , comboboxTilt{ ComboBox{this} }
    , comboboxAnimCount{ ComboBox{this, {"5", "10", "15", "20", "25", "30", "40", "50"}} }
    , comboboxAnimSpeed{ ComboBox{this} }
    , animateButton{ ButtonToggle{this, Play, "Animate ctrl-a"} }
    , reloadButton{ ButtonToggle{this, Update, "Auto Update ctrl-u"} }
    , settingsButton{ Button{this, Settings, "Settings ctrl-p"} }
    , moveLeftButton{ Button{this, Left, "Move left ctrl- <-"} }
    , moveRightButton{ Button{this, Right, "Move right ctrl- ->"} }
    , moveDownButton{ Button{this, Down, "Move down ctrl- downArrow"} }
    , moveUpButton{ Button{this, Up, "Move up ctrl- upArrow"} }
    , zoomOutButton{ Button{this, Minus, "Zoom out ctrl- -"} }
    , zoomInButton{ Button{this, Plus, "Zoom in ctrl- +"} }
    , textFrameCount{ Text{this, "Frame Count:"} }
    , textTilt{ Text{this, "Tilt:"} }
    , textAnimSpeed{ Text{this, "Anim Speed:"} }
    , nexradLayerDownload{ NexradLayerDownload{this, &nexradList} }
    , objectAnimateNexrad{ ObjectAnimateNexrad{this, &nexradList, &animateButton, &comboboxAnimCount, &comboboxAnimSpeed} }
    , shortcutReload{ Shortcut{QKeySequence{"U"}, this} }
    , shortcutU{ Shortcut{QKeySequence{"V"}, this} }
    , shortcutQ{ Shortcut{QKeySequence{"R"}, this} }
    , shortcutL{ Shortcut{QKeySequence{"L"}, this} }
    , shortcutT{ Shortcut{QKeySequence{"T"}, this} }
    , shortcutC{ Shortcut{QKeySequence{"C"}, this} }
    , shortAnimate{ Shortcut{QKeySequence{"A"}, this} }
    , shortcutZoomIn{ Shortcut{Qt::Key_Equal, this} }  // was Shortcut{Qt::CTRL | Qt::Key_Equal, this)
    , shortcutZoomOut{ Shortcut{Qt::Key_Minus, this} }
    , shortcutMoveLeft{ Shortcut{Qt::Key_Left, this} }
    , shortcutMoveRight{ Shortcut{Qt::Key_Right, this} }
    , shortcutMoveUp{ Shortcut{Qt::Key_Up, this} }
    , shortcutMoveDown{ Shortcut{Qt::Key_Down, this} }
    , shortcutKeyboard{ Shortcut{QKeySequence{"/"}, this} }
    , shortcutSettings{ Shortcut{QKeySequence{"P"}, this} }
{
    setTitle("Nexrad Radar");
    setAttribute(Qt::WA_DeleteOnClose);
    //
    // Determine dimensions
    //
    const auto dimens = UtilityUI::getScreenBounds();
    const auto widthW = dimens[0];
    const auto heightW = dimens[1];
    auto dimen = std::max(widthW, heightW);
    setFixedWidth(widthW);
    setFixedHeight(heightW);

    if (numberOfPanes == 4) {
        dimen = static_cast<int>(std::round(dimen / 2.0));
    }

    // Emit updates every 10 seconds if available
    // source = QGeoPositionInfoSource::createDefaultSource(this);
    // if (RadarPreferences::locdotFollowsGps) {
    //     if (source) {
    //         qDebug() << "emit every 10 sec";
    //         source->setUpdateInterval(10000);
    //         // source->positionUpdated.connect(self.positionUpdated);
    //         QObject::connect(source, &QGeoPositionInfoSource::positionUpdated, this, [this] (const QGeoPositionInfo& g) { positionUpdated(g); });
    //         source->startUpdates();
    //     } else {
    //         qDebug() << "failed to setup location";
    //     }
    // }

    //
    // Initialize main layout containers
    //
    setStatusBar(statusBar.getView());
    statusBar.setVisible(RadarPreferences::radarShowStatusBar);
    box.setSpacing(0);
    toolbarLayout.setSpacing(2);
    radarLayout.setSpacing(0);
    radarLayout2.setSpacing(0);
    //
    // Initialize NexradWidgets
    //
    for (auto index : range(numberOfPanes)) {
        nexradList.push_back(
            new NexradWidget{
                this,
                statusBar,
                index,
                numberOfPanes,
                useASpecificRadar,
                radarSite,
                widthW,
                heightW,
                [this] (int pane, const auto& prod) { changeProductFromChild(prod, pane); },
                [this] (int pane, const auto& sector) { changeSectorFromChild(sector, pane); },
                [this] (double z, int pane) { changeZoom(z, pane); },
                [this] (int pane) { updateDrag(pane); }
            });
        nexradList.back()->setFixedHeight(dimen);
        nexradList.back()->setFixedWidth(dimen);
    }
    //
    // Add NexradWidgets to layouts
    //
    radarLayout.addWidget(nexradList[0]);
    if (numberOfPanes > 1) {
        radarLayout.addWidget(nexradList[1]);
    }
    if (numberOfPanes == 4) {
        radarLayout2.addWidget(nexradList[2]);
        radarLayout2.addWidget(nexradList[3]);
    }
    setupDropDowns();
    setupShortCuts();
    setupToolbar();
    setupBoxLayout();
    downloadData();
}

void Nexrad::setupDropDowns() {
    settingsButton.connect([this] {
        new SettingsMain{this, [this] { settingsCheck(); downloadData(); }, true, true};
    });
    //
    // sector menu
    //
    comboboxSector.setIndexByValue(nexradList[0]->nexradState.getRadarSite());
    comboboxSector.connect([this] { changeRadarSite(); });
    //
    // product menu
    //
    comboboxProduct.setIndexByValue(nexradList[0]->nexradState.getRadarProduct());
    comboboxProduct.connect([this] { changeProduct(); });
    //
    // reload
    //
    reloadButton.setCheckable(true);
    reloadButton.connect([this] { toggleAutoUpdate(); });
    moveLeftButton.connect([this] { changePosition(-100.0, 0.0); });
    moveRightButton.connect([this] { changePosition(100.0, 0.0); });
    moveDownButton.connect([this] { changePosition(0.0, 100.0); });
    moveUpButton.connect([this] { changePosition(0.0, -100.0); });
    zoomOutButton.connect([this] { changeZoom(0.77, 0); });
    zoomInButton.connect([this] { changeZoom(1.33, 0); });

    comboboxAnimCount.setIndex(Utility::readPrefInt("NEXRAD_ANIM_FRAME_COUNT2", 1));

    comboboxTilt.setArrayListInt(range(4));
    comboboxTilt.setIndex(nexradList[0]->nexradState.tiltInt);
    comboboxTilt.connect([this] { changeTilt(); });

    comboboxAnimSpeed.setArrayListInt(range2(1, 20));
    comboboxAnimSpeed.setIndex(Utility::readPrefInt("ANIM_INTERVAL", 5));

    comboboxAnimCount.connect([this] { objectAnimateNexrad.setAnimationCount(); });
    comboboxAnimSpeed.connect([this] { objectAnimateNexrad.setAnimationSpeed(); });
    animateButton.connect([this] { objectAnimateNexrad.animateClicked(); });
}

void Nexrad::setupToolbar() {
    toolbarLayout.addWidget(settingsButton);
    toolbarLayout.addWidget(comboboxSector);
    toolbarLayout.addWidget(comboboxProduct);
    toolbarLayout.addWidget(moveLeftButton);
    toolbarLayout.addWidget(moveRightButton);
    toolbarLayout.addWidget(moveUpButton);
    toolbarLayout.addWidget(moveDownButton);
    toolbarLayout.addWidget(zoomOutButton);
    toolbarLayout.addWidget(zoomInButton);
    toolbarLayout.addWidget(reloadButton);
    toolbarLayout.addWidget(animateButton);
    toolbarLayout.addWidget(textFrameCount, 0, Qt::AlignCenter);
    toolbarLayout.addWidget(comboboxAnimCount);
    toolbarLayout.addWidget(textTilt, 0, Qt::AlignCenter);
    toolbarLayout.addWidget(comboboxTilt);
    toolbarLayout.addWidget(textAnimSpeed, 0, Qt::AlignCenter);
    toolbarLayout.addWidget(comboboxAnimSpeed);
    for (auto nw : nexradList) {
        toolbarLayout.addWidget(nw->nexradState.radarStatusBox->get());
    }
    box.addLayout(toolbarLayout);
    if (!RadarPreferences::radarShowControls) {
        moveLeftButton.setVisible(false);
        moveRightButton.setVisible(false);
        moveUpButton.setVisible(false);
        moveDownButton.setVisible(false);
        zoomOutButton.setVisible(false);
        zoomInButton.setVisible(false);
    }
}

void Nexrad::setupBoxLayout() {
    box.addLayout(radarLayout);
    if (numberOfPanes == 4) {
        box.addLayout(radarLayout2);
    }
    box.getAndShow(this);
}

void Nexrad::setupShortCuts() {
    shortcutReload.connect([this] { toggleAutoUpdate(); });
    shortcutU.connect([this] { changeProductFromChild("N0U", 0); });
    shortcutQ.connect([this] { changeProductFromChild("N0Q", 0); });
    shortcutL.connect([this] { changeProductFromChild("DVL", 0); });
    shortcutT.connect([this] { changeProductFromChild("EET", 0); });
    shortcutC.connect([this] { changeProductFromChild("N0C", 0); });
    shortAnimate.connect([this] {
        objectAnimateNexrad.animateClicked();
        animateButton.setChecked(!animateButton.isChecked());
    });
    shortcutZoomIn.connect([this] { changeZoom(1.33, 0); });
    shortcutZoomOut.connect([this] { changeZoom(0.77, 0); });
    shortcutMoveLeft.connect([this] { changePosition(-1.0 * moveIncrement, 0.0); });
    shortcutMoveRight.connect([this] { changePosition(moveIncrement, 0.0); });
    shortcutMoveUp.connect([this] { changePosition(0.0, -1.0 * moveIncrement); });
    shortcutMoveDown.connect([this] { changePosition(0.0, moveIncrement); });
    shortcutKeyboard.connect([this] { new TextViewerStatic{this, GlobalVariables::nexradShortcuts, 700, 600}; });
    shortcutSettings.connect([this] { new SettingsMain{this, [this] { downloadData(); }, true, true}; });
}

Nexrad::~Nexrad() {
    for (auto nw : nexradList) {
        delete nw;
    }
}

void Nexrad::syncRadarSite(const string& radarSite, int pane) {
    moveLeftButton.setVisible(RadarPreferences::radarShowControls);
    moveRightButton.setVisible(RadarPreferences::radarShowControls);
    moveUpButton.setVisible(RadarPreferences::radarShowControls);
    moveDownButton.setVisible(RadarPreferences::radarShowControls);
    zoomOutButton.setVisible(RadarPreferences::radarShowControls);
    zoomInButton.setVisible(RadarPreferences::radarShowControls);
    statusBar.setVisible(RadarPreferences::radarShowStatusBar);

    if (RadarPreferences::dualpaneshareposn) {
        for (auto nw : nexradList) {
            nw->nexradState.setRadar(radarSite);
            nw->nexradState.reset();
            nw->nexradDraw.initGeom();
            // UtilityNexradDraw::initGeom(nw->nexradState, nw->fileStorage, nw->textObject);
        }
    } else {
        nexradList[pane]->nexradState.setRadar(radarSite);
        nexradList[pane]->nexradState.reset();
        nexradList[pane]->nexradDraw.initGeom();
        // UtilityNexradDraw::initGeom(nexradList[pane]->nexradState, nexradList[pane]->fileStorage, nexradList[pane]->textObject);
    }
}

void Nexrad::downloadData() {
    objectAnimateNexrad.stopAnimate();
    for (auto nw : nexradList) {
        nw->downloadData();
    }
    nexradLayerDownload.downloadLayers();
    if (reloadTimer.isActive()) {
        updateTitleForAutoRefresh();
    }
}

void Nexrad::updateTitleForAutoRefresh() {
    setTitle("Auto update [on], interval " + To::string(RadarPreferences::dataRefreshInterval) + ", last update: " + ObjectDateTime::getLocalTimeAsString());
}

void Nexrad::autoUpdate() {
    updateTitleForAutoRefresh();
    downloadData();
}

void Nexrad::closeEvent(QCloseEvent * event) {
    if (reloadTimer.isActive()) {
        reloadTimer.stop();
    }
    objectAnimateNexrad.stopAnimateNoDownload();
    for (auto it : nexradList) {
        it->nexradState.writePreferences();
    }
    event->accept();
}

void Nexrad::changePosition(double x, double y) {
    if (RadarPreferences::dualpaneshareposn) {
        for (auto nw : nexradList) {
            nw->nexradState.xPos -= x;
            nw->nexradState.yPos -= y;
            nw->update();
        }
    } else {
        nexradList[0]->nexradState.xPos -= x;
        nexradList[0]->nexradState.yPos -= y;
        nexradList[0]->update();
    }
}

void Nexrad::toggleAutoUpdate() {
    if (reloadTimer.isActive()) {
        UtilityLog::d("Timer DISABLED");
        reloadButton.setChecked(false);
        reloadTimer.stop();
        setTitle("Nexrad Radar");
    } else {
        UtilityLog::d("Timer ENABLED");
        objectAnimateNexrad.stopAnimateNoDownload();
        reloadButton.setChecked(true);
        // timer interval is in milliseconds so x 1000 to get seconds and then x 60 to get minutes
        reloadTimer.start(RadarPreferences::dataRefreshInterval * 1000 * 60);
    }
    downloadData();
}

void Nexrad::changeZoom(double changeAmount, int paneIndex) {
    const auto factor = static_cast<float>(changeAmount);
    if (RadarPreferences::dualpaneshareposn) {
        for (auto nw : nexradList) {
            const auto oldZoom = nw->nexradState.zoom;
            nw->nexradState.zoom *= factor;

            const auto newZoom = nw->nexradState.zoom;
            const auto zoomDifference = newZoom / oldZoom;

            nw->nexradState.xPos *= zoomDifference;
            nw->nexradState.yPos *= zoomDifference;

            nw->resizePolygons();
            nw->textObject.add();
            nw->update();
        }
    } else {
        const auto oldZoom = nexradList[paneIndex]->nexradState.zoom;
        nexradList[paneIndex]->nexradState.zoom *= factor;

        const auto newZoom = nexradList[paneIndex]->nexradState.zoom;
        const auto zoomDifference = newZoom / oldZoom;

        nexradList[paneIndex]->nexradState.xPos *= zoomDifference;
        nexradList[paneIndex]->nexradState.yPos *= zoomDifference;

        nexradList[paneIndex]->resizePolygons();
        nexradList[paneIndex]->textObject.add();
        nexradList[paneIndex]->update();
    }
}

void Nexrad::updateDrag(int originIndex) {
    if (RadarPreferences::dualpaneshareposn) {
        for (auto nw : nexradList) {
            nw->nexradState.xPos = nexradList[originIndex]->nexradState.xPos;
            nw->nexradState.yPos = nexradList[originIndex]->nexradState.yPos;
            nw->update();
        }
    }
}

void Nexrad::changeTilt() {
    const auto tilt = comboboxTilt.getIndex();
    if (tilt != nexradList[0]->nexradState.tiltInt) {
        for (auto nw : nexradList) {
            nw->nexradState.tiltInt = tilt;
        }
        downloadData();
    }
}

// KEEP
// void Nexrad::positionUpdated(const QGeoPositionInfo& info) {
//     auto coord = info.coordinate();
//     auto lat = coord.latitude();
//     auto lon = coord.longitude();
//     qDebug() << "updated GPS: " << lat << " " << lon;
//     for (auto nw : nexradList) {
//         nw->updateGps(lat, lon);
//         nw->update();
//     }
// }

void Nexrad::changeProduct() {
    objectAnimateNexrad.stopAnimateNoDownload();
    const auto prod = comboboxProduct.getValue();
    nexradLayerDownload.downloadLayers();
    nexradList[0]->changeProduct(prod);
}

void Nexrad::changeProductFromChild(const string& productF, int paneNumber) {
    objectAnimateNexrad.stopAnimateNoDownload();
    const auto product = WString::split(productF, ":")[0];
    // TODO FIXME need to update combobox if tdwr, comboboxProduct.onAction = {}
    if (paneNumber == 0 && !NexradUtil::isProductTdwr(product)) {
        const auto productIndex = findex(product, NexradUtil::radarProductList);
        comboboxProduct.block();
        comboboxProduct.setIndex(productIndex);
        comboboxProduct.unblock();
    }
    nexradLayerDownload.downloadLayers();
    nexradList[paneNumber]->changeProduct(product);
}

void Nexrad::changeRadarSite() {
    const auto site = comboboxSector.getValue();
    const auto radarSite = WString::split(site, ":")[0];
    syncRadarSite(radarSite, 0);
    downloadData();
}

void Nexrad::changeSectorFromChild(const string& radarSite, int paneNumber) {
    const auto sectorIndex = findex(radarSite, GlobalArrays::radars());
    comboboxSector.block();
    comboboxSector.setIndex(sectorIndex);
    comboboxSector.unblock();
    syncRadarSite(radarSite, paneNumber);
    downloadData();
}

void Nexrad::settingsCheck() {
    moveLeftButton.setVisible(RadarPreferences::radarShowControls);
    moveRightButton.setVisible(RadarPreferences::radarShowControls);
    moveUpButton.setVisible(RadarPreferences::radarShowControls);
    moveDownButton.setVisible(RadarPreferences::radarShowControls);
    zoomOutButton.setVisible(RadarPreferences::radarShowControls);
    zoomInButton.setVisible(RadarPreferences::radarShowControls);
    statusBar.setVisible(RadarPreferences::radarShowStatusBar);
    RadarGeometry::initialize();
    RadarPreferences::initialize();
    for (auto nw : nexradList) {
        nw->textObject.initialize();
        nw->nexradDraw.initGeom();
    }
    if (reloadTimer.isActive()) {
        // timer interval is in milliseconds so x 1000 to get seconds and then x 60 to get minutes
        reloadTimer.setInterval(RadarPreferences::dataRefreshInterval * 1000 * 60);
        updateTitleForAutoRefresh();
    }
}
