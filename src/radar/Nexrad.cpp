// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/Nexrad.h"
#include <cmath>
#include <QKeySequence>
#include "common/GlobalArrays.h"
#include "common/GlobalVariables.h"
#include "misc/TextViewerStatic.h"
#include "radar/WXGLNexrad.h"
#include "settings/RadarPreferences.h"
#include "settings/SettingsMain.h"
#include "ui/Icon.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityList.h"
#include "util/UtilityLog.h"
#include "util/UtilityTime.h"
#include "util/UtilityUI.h"

Nexrad::Nexrad(QWidget * parent, int numberOfPanes, bool useASpecificRadar, const QString& radarSite, bool savePrefs) : Window(parent) {
    this->numberOfPanes = numberOfPanes;
    this->savePrefs = savePrefs;
    //
    // if the nexrad viewer is called from severe dash or mcd viewer with a specific
    // radar then the following is needed
    //
    this->useASpecificRadar = useASpecificRadar;
    this->radarSite = radarSite;
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
    setFixedHeight(heightW - 30);
    if (numberOfPanes == 4) {
        dimen = std::round(dimen / 2.0);
    }
    //
    // Initialize main layout containers
    //
    statusBar = StatusBar(this);
    setStatusBar(statusBar.get());
    statusBar.setVisible(RadarPreferences::radarShowStatusBar);
    box = VBox(this);
    box.setSpacing(0);
    toolbarLayout = HBox(this);
    toolbarLayout.setSpacing(2);
    radarLayout = HBox(this);
    radarLayout.setSpacing(0);
    radarLayout2 = HBox(this);
    radarLayout2.setSpacing(0);
    //
    // Initialize NexradWidgets
    //
    for (auto index : UtilityList::range(numberOfPanes)) {
        radarStatusBoxList.push_back(new RadarStatusBox(this));
        nexradList.push_back(
            new NexradWidget(
                this,
                statusBar,
                radarStatusBoxList[index],
                index,
                numberOfPanes,
                useASpecificRadar,
                radarSite,
                dimen,
                dimen,
                widthW,
                heightW,
                [this] (int pane, QString prod) { changeProductForPane(pane, prod); },
                [this] (int pane, QString sector) { changeSectorBySite(pane, sector); },
                [this] (double z, int pane) { changeZoom(z, pane); },
                [this] (int pane) { updateDrag(pane); }
            )
        );
        nexradList.back()->setFixedHeight(dimen);
        nexradList.back()->setFixedWidth(dimen);
    }
    nexradLayerDownload = new NexradLayerDownload(this, nexradList);
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
    settingsButton = Button(this, Icon::Settings, "Settings ctrl-p");
    settingsButton.connect([this] { 
        new SettingsMain(this, nullptr, [this] {
            settingsCheck();
            downloadData();
        }, false);
    });
    //
    // sector menu
    //
    comboboxSector = ComboBox(this, GlobalArrays::radars());
    comboboxSector.setIndexByValue(nexradList[radarIndex]->nexradState.radarSite);
    comboboxSector.connect([this] { changeSector(); });
    //
    // product menu
    //
    comboboxProduct = ComboBox(this, WXGLNexrad::radarProductList);
    comboboxProduct.setIndexByValue(nexradList[radarIndex]->nexradState.radarProduct);
    comboboxProduct.connect([this] { changeProduct(); });
    //
    // reload
    //
    reloadButton = ButtonToggle(this, Icon::Update, "Auto Update ctrl-u");
    reloadButton.setCheckable(true);
    reloadButton.connect([this] { reload(); });
    reloadTimer = new Timer(this, [this] { autoUpdate(); });

    moveLeft = Button(this, Icon::Left, "Move left ctrl- <-");
    moveLeft.connect([this] { moveLeftClicked(); });

    moveRight = Button(this, Icon::Right, "Move right ctrl- ->");
    moveRight.connect([this] { moveRightClicked(); });

    moveDown = Button(this, Icon::Down, "Move down ctrl- downArrow");
    moveDown.connect([this] { moveDownClicked(); });

    moveUp = Button(this, Icon::Up, "Move up ctrl- upArrow");
    moveUp.connect([this] { moveUpClicked(); });

    zoomOut = Button(this, Icon::Minus, "Zoom out ctrl- -");
    zoomOut.connect([this] { zoomOutClicked(); });

    zoomIn = Button(this, Icon::Plus, "Zoom in ctrl- +");
    zoomIn.connect([this] { zoomInClicked(); });

    textFrameCount = Text(this, "Frame Count:");
    QStringList frameCountList = {"5", "10", "15", "20", "25", "30", "40", "50"};
    comboboxAnimCount = ComboBox(this, frameCountList);
    comboboxAnimCount.setIndex(Utility::readPrefInt("NEXRAD_ANIM_FRAME_COUNT2", 1));

    textTilt = Text(this, "Tilt:");
    comboboxTilt = ComboBox(this);
    comboboxTilt.setArrayListInt(UtilityList::range(4));
    comboboxTilt.setIndex(nexradList[0]->nexradState.tiltInt);
    comboboxTilt.connect([this] { changeTilt(); });

    textAnimSpeed = Text(this, "Anim Speed:");
    comboboxAnimSpeed = ComboBox(this);
    comboboxAnimSpeed.setArrayListInt(UtilityList::range2(1, 10));
    comboboxAnimSpeed.setIndex(Utility::readPrefInt("ANIM_INTERVAL", 5));

    objectAnimateNexrad = new ObjectAnimateNexrad(this, nexradList, &animateButton, &comboboxAnimCount, &comboboxAnimSpeed);
    comboboxAnimCount.connect([this] { objectAnimateNexrad->setAnimationCount(); });
    comboboxAnimSpeed.connect([this] { objectAnimateNexrad->setAnimationSpeed(); });
    animateButton = ButtonToggle(this, Icon::Play, "Animate ctrl-a");
    animateButton.connect([this] { objectAnimateNexrad->animateClicked(); });
}

void Nexrad::setupToolbar() {
    toolbarLayout.addWidget(settingsButton.get());
    toolbarLayout.addWidget(comboboxSector.get());
    toolbarLayout.addWidget(comboboxProduct.get());
    toolbarLayout.addWidget(moveLeft.get());
    toolbarLayout.addWidget(moveRight.get());
    toolbarLayout.addWidget(moveUp.get());
    toolbarLayout.addWidget(moveDown.get());
    toolbarLayout.addWidget(zoomOut.get());
    toolbarLayout.addWidget(zoomIn.get());
    toolbarLayout.addWidget(reloadButton.get());
    toolbarLayout.addWidget(animateButton.get());
    toolbarLayout.addWidget(textFrameCount.get(), 0, Qt::AlignCenter);
    toolbarLayout.addWidget(comboboxAnimCount.get());
    toolbarLayout.addWidget(textTilt.get(), 0, Qt::AlignCenter);
    toolbarLayout.addWidget(comboboxTilt.get());
    toolbarLayout.addWidget(textAnimSpeed.get(), 0, Qt::AlignCenter);
    toolbarLayout.addWidget(comboboxAnimSpeed.get());
    for (auto& timeLabel : radarStatusBoxList) {
        toolbarLayout.addWidget(timeLabel->get());
    }
    box.addLayout(toolbarLayout.get());
    if (!RadarPreferences::radarShowControls) {
        moveLeft.setVisible(false);
        moveRight.setVisible(false);
        moveUp.setVisible(false);
        moveDown.setVisible(false);
        zoomOut.setVisible(false);
        zoomIn.setVisible(false);
    }
}

void Nexrad::setupBoxLayout() {
    box.addLayout(radarLayout.get());
    if (numberOfPanes == 4) {
        box.addLayout(radarLayout2.get());
    }
    box.getAndShow(this);
}

void Nexrad::setupShortCuts() {
    shortcutReload = Shortcut(QKeySequence("Ctrl+U"), this);
    shortcutReload.connect([this] { reload(); });

    shortcutU = Shortcut(QKeySequence("Ctrl+V"), this);
    shortcutU.connect([this] { changeProductForPane(0, "N0U"); });

    shortcutQ = Shortcut(QKeySequence("Ctrl+R"), this);
    shortcutQ.connect([this] { changeProductForPane(0, "N0Q"); });

    shortcutL = Shortcut(QKeySequence("Ctrl+L"), this);
    shortcutL.connect([this] { changeProductForPane(0, "DVL"); });

    shortcutT = Shortcut(QKeySequence("Ctrl+T"), this);
    shortcutT.connect([this] { changeProductForPane(0, "EET"); });

    shortcutC = Shortcut(QKeySequence("Ctrl+C"), this);
    shortcutC.connect([this] { changeProductForPane(0, "N0C"); });

    shortAnimate = Shortcut(QKeySequence("Ctrl+A"), this);
    shortAnimate.connect([this] { objectAnimateNexrad->animateClicked(); });

    shortcutZoomOut = Shortcut(Qt::CTRL | Qt::Key_Equal, this);
    shortcutZoomOut.connect([this] { zoomInClicked(); });

    shortcutZoomIn = Shortcut(Qt::CTRL | Qt::Key_Minus, this);
    shortcutZoomIn.connect([this] { zoomOutClicked(); });

    shortcutMoveLeft = Shortcut(Qt::CTRL | Qt::Key_Left, this);
    shortcutMoveLeft.connect([this] { moveLeftClicked(); });

    shortcutMoveRight = Shortcut(Qt::CTRL | Qt::Key_Right, this);
    shortcutMoveRight.connect([this] { moveRightClicked(); });

    shortcutMoveUp = Shortcut(Qt::CTRL | Qt::Key_Up, this);
    shortcutMoveUp.connect([this] { moveUpClicked(); });

    shortcutMoveDown = Shortcut(Qt::CTRL | Qt::Key_Down, this);
    shortcutMoveDown.connect([this] { moveDownClicked(); });

    shortcutKeyboard = Shortcut(QKeySequence("Ctrl+/"), this);
    shortcutKeyboard.connect([this] { new TextViewerStatic(this, GlobalVariables::nexradShortcuts, 700, 600); });

    shortcutSettings = Shortcut(QKeySequence("Ctrl+P"), this);
    shortcutSettings.connect([this] { new SettingsMain(this, nullptr, [this] { downloadData(); }, false); });
}

Nexrad::~Nexrad() {
    for (auto nw : nexradList) {
        delete nw;
    }
}

void Nexrad::downloadData() {
    for (auto nw : nexradList) {
        nw->downloadData();
    }
    nexradLayerDownload->downloadLayers();
}

void Nexrad::updateTitleForAutoRefresh() {
    setTitle("Auto update [on], interval " + To::String(RadarPreferences::dataRefreshInterval) + ", last update: " + UtilityTime::getLocalTimeAsString());
}

void Nexrad::autoUpdate() {
    updateTitleForAutoRefresh();
    downloadData();
}

void Nexrad::changeProduct() {
    auto index = comboboxProduct.getIndex();
    objectAnimateNexrad->stopAnimate();
    nexradList[radarIndex]->changeProduct(index);
    writePreferences();
    nexradLayerDownload->downloadLayers();
}

void Nexrad::changeProductForPane(int paneNumber, const QString& product) {
    objectAnimateNexrad->stopAnimate();
    if (paneNumber == 0) {
        auto productIndex = UtilityList::findex(product, WXGLNexrad::radarProductList);
        comboboxProduct.block(0);
        comboboxProduct.setIndex(productIndex);
        comboboxProduct.unblock(0);
    }
    nexradList[paneNumber]->nexradState.radarProduct = product;
    writePreferences();
    nexradList[paneNumber]->initColorLegend();
    nexradList[paneNumber]->downloadData();
    nexradLayerDownload->downloadLayers();
}

void Nexrad::changeSector() {
    auto indexSector = comboboxSector.getIndex();
    if (RadarPreferences::dualpaneshareposn) {
        for (auto nw : nexradList) {
            nw->changeSector(indexSector);
        }
    } else {
        nexradList[radarIndex]->changeSector(indexSector);
    }
    writePreferences();
    nexradLayerDownload->downloadLayers();
}

void Nexrad::closeEvent(QCloseEvent * event) {
    if (!useASpecificRadar) {
        writePreferences();
    }
    if (objectAnimateNexrad->isAnimating()) {
        objectAnimateNexrad->stopAnimate();
    }
    reloadTimer->stop();
    event->accept();
}

void Nexrad::writePreferences() {
    if (savePrefs) {
        for (auto nw : nexradList) {
            nw->nexradState.writePreferences();
        }
    }
}

void Nexrad::zoomInClicked() {
    changeZoom(1.33, 0);
}

void Nexrad::zoomOutClicked() {
    changeZoom(0.77, 0);
}

void Nexrad::moveLeftClicked() {
    if (RadarPreferences::dualpaneshareposn) {
        for (auto nw : nexradList) {
            nw->nexradState.xPos += movementSize;
            nw->update();
        }
    } else {
        nexradList[radarIndex]->nexradState.xPos += movementSize;
        nexradList[radarIndex]->update();
    }
}

void Nexrad::moveRightClicked() {
    if (RadarPreferences::dualpaneshareposn) {
        for (auto nw : nexradList) {
            nw->nexradState.xPos -= movementSize;
            nw->update();
        }
    } else {
        nexradList[radarIndex]->nexradState.xPos -= movementSize;
        nexradList[radarIndex]->update();
    }
}

void Nexrad::moveUpClicked() {
    if (RadarPreferences::dualpaneshareposn) {
        for (auto nw : nexradList) {
            nw->nexradState.yPos += movementSize;
            nw->update();
        }
    } else {
        nexradList[radarIndex]->nexradState.yPos += movementSize;
        nexradList[radarIndex]->update();
    }
}

void Nexrad::moveDownClicked() {
    if (RadarPreferences::dualpaneshareposn) {
        for (auto nw : nexradList) {
            nw->nexradState.yPos -= movementSize;
            nw->update();
        }
    } else {
        nexradList[radarIndex]->nexradState.yPos -= movementSize;
        nexradList[radarIndex]->update();
    }
}

void Nexrad::reload() {
    downloadData();
    if (reloadTimer->isActive()) {
        UtilityLog::d("Timer DISABLED");
        reloadButton.setChecked(false);
        reloadTimer->stop();
        setTitle("Nexrad Radar");
    } else {
        UtilityLog::d("Timer ENABLED");
        reloadButton.setChecked(true);
        // timer internval is in milliseconds so x 1000 to get seconds and then x 60 to get minutes
        reloadTimer->start(RadarPreferences::dataRefreshInterval * 1000 * 60);
        updateTitleForAutoRefresh();
    }
}

void Nexrad::updateStatusBar() {
    for (auto paneNumber : UtilityList::range(nexradList.size())) {
        nexradList[paneNumber]->statusBarLabel.setText(nexradList[paneNumber]->fileStorage.radarInfo);
    }
}

void Nexrad::changeZoom(double changeAmount, int paneIndex) {
    const auto factor = static_cast<float>(changeAmount);
    if (RadarPreferences::dualpaneshareposn) {
        for (auto nw : nexradList) {

            // double xMiddle = nw->windowWidth;
            // double yMiddle = nw->windowHeight;
            // nw->xPos += nw->xPos * (nw->zoom / factor);
            // nw->yPos += nw->yPos * (nw->zoom / factor);

            // qDebug() << nw->xPos;

            // nw->xPos += (location.x - xMiddle) * density)
            // nw->yPos += ((yMiddle - location.y) * density)

            //nw->nexradState.zoom *= factor;

            double oldZoom = nw->nexradState.zoom;
            nw->nexradState.zoom *= factor;
            double zoomDifference = nw->nexradState.zoom / oldZoom;

            nw->nexradState.xPos *= zoomDifference;
            //nw->nexradState.yPos *= zoomDifference;

            nw->resizePolygons();
            nw->textObject->add();
            nw->update();
        }
    } else {
        nexradList[paneIndex]->nexradState.zoom *= factor;
        nexradList[paneIndex]->resizePolygons();
        nexradList[paneIndex]->textObject->add();
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

void Nexrad::changeSectorBySite(int paneNumber, const QString& radarSite) {
    objectAnimateNexrad->stopAnimate();
    radarIndex = paneNumber;
    const auto sectorIndex = UtilityList::findex(radarSite, GlobalArrays::radars());
    comboboxSector.block(0);
    comboboxSector.setIndex(sectorIndex);
    comboboxSector.unblock(0);
    if (RadarPreferences::dualpaneshareposn) {
        for (auto nw : nexradList) {
            nw->changeSector(radarSite);
        }
    } else {
        nexradList[radarIndex]->changeSector(radarSite);
    }
    nexradLayerDownload->downloadLayers();
}

void Nexrad::changeTilt() {
    int tilt = comboboxTilt.getIndex();
    if (tilt != nexradList[0]->nexradState.tiltInt ) {
        for (auto nw : nexradList) {
            nw->nexradState.tiltInt = tilt;
        }
        downloadData();
    }
}

void Nexrad::settingsCheck() {
    moveLeft.setVisible(RadarPreferences::radarShowControls);
    moveRight.setVisible(RadarPreferences::radarShowControls);
    moveUp.setVisible(RadarPreferences::radarShowControls);
    moveDown.setVisible(RadarPreferences::radarShowControls);
    zoomOut.setVisible(RadarPreferences::radarShowControls);
    zoomIn.setVisible(RadarPreferences::radarShowControls);

    statusBar.setVisible(RadarPreferences::radarShowStatusBar);

    for (auto nw : nexradList) {
        nw->textObject->initialize();
        nw->initializeGeomBuffers();
        nw->initializeGeom();
    }

    if (reloadTimer->isActive()) {
        // timer internval is in milliseconds so x 1000 to get seconds and then x 60 to get minutes
        reloadTimer->setInterval(RadarPreferences::dataRefreshInterval * 1000 * 60);
        updateTitleForAutoRefresh();
    }
}
