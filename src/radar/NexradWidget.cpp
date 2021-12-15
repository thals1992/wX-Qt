// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradWidget.h"
#include <QApplication>
#include <QMenu>
#include <QMessageBox>
#include <QPainter>
#include <cmath>
#include "common/GlobalArrays.h"
#include "common/GlobalVariables.h"
#include "misc/TextViewer.h"
#include "objects/Color.h"
#include "objects/RadarGeometry.h"
#include "radar/Nexrad.h"
#include "radar/UtilityMetar.h"
#include "radar/UtilityRadarUI.h"
#include "radar/UtilitySpotter.h"
#include "radar/UtilitySwoDay1.h"
#include "radar/UtilityWatch.h"
#include "radar/UtilityWpcFronts.h"
#include "radar/WXGLDownload.h"
#include "radar/WXGLNexrad.h"
#include "radar/WXGLNexradLevel3WindBarbs.h"
#include "radar/WXGLPolygonWarnings.h"
#include "settings/Location.h"
#include "settings/RadarPreferences.h"
#include "settings/UtilityLocation.h"
#include "ui/Action.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityCanvasProjection.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"
#include "util/UtilityTime.h"

NexradWidget::NexradWidget() {
}

NexradWidget::NexradWidget(
    QWidget * parent,
    StatusBar& statusBar,
    RadarStatusBox * radarStatusBox,
    int paneNumber,
    int numberOfPanes,
    bool useASpecificRadar,
    QString radarToUse,
    int widthF,
    int heightF,
    int originalWidthF,
    int originalHeightF,
    std::function<void(int, QString)> fnProduct,
    std::function<void(int, QString)> fnSector,
    std::function<void(double, int)> fnZoom,
    std::function<void(int)> fnPosition
) : QWidget(parent) {

    setAttribute(Qt::WA_DeleteOnClose);

    this->statusBar = &statusBar;
    this->radarStatusBox = radarStatusBox;
    this->fnProduct = fnProduct;
    this->fnSector = fnSector;
    this->fnZoom = fnZoom;
    this->fnPosition = fnPosition;

    nexradState = NexradState(paneNumber, numberOfPanes, useASpecificRadar);
    nexradState.windowWidth = widthF;
    nexradState.windowHeight = heightF;
    originalWidth = originalWidthF;
    originalHeight = originalHeightF;

    statusBarLabel = Text(this, "");
    statusBarLabel.setWrap(false);
    this->statusBar->addWidget(statusBarLabel.get());

    mouseStartX = 0.0;
    mouseStartY = 0.0;
    resetZoom();
    textObject.reset(new WXMetalTextObject(1, originalWidth, originalHeight, nexradState, 1.0, &fileStorage));

    //
    // set initital preferences
    //
    if (!nexradState.useASpecificRadar) {
        nexradState.radarSite = Location::radar();
        nexradState.radarProduct = nexradState.initialRadarProducts[0];
        nexradState.readPreferences();
    } else {
        nexradState.radarSite = radarToUse;
        nexradState.radarProduct = nexradState.initialRadarProducts[0];
    }

    initColorLegend();

    polygonToColorMap[PolygonType::ffw] = RadarPreferences::colorFfw;
    polygonToColorMap[PolygonType::tst] = RadarPreferences::colorTstorm;
    polygonToColorMap[PolygonType::tor] = RadarPreferences::colorTor;
    polygonToColorMap[PolygonType::mpd] = RadarPreferences::colorMpd;
    polygonToColorMap[PolygonType::mcd] = RadarPreferences::colorMcd;
    polygonToColorMap[PolygonType::watch] = RadarPreferences::colorTstormWatch;
    polygonToColorMap[PolygonType::watchTornado] = RadarPreferences::colorTorWatch;

    initializeGeomBuffers();
    radarBuffers = ObjectMetalRadarBuffers();
    levelData = WXMetalNexradLevelData(nexradState.radarProduct, &radarBuffers, To::String(nexradState.paneNumber));
    nexradState.pn = ProjectionNumbers(nexradState.radarSite);
    show();
    initializeGeom();
}

//
// The main method that draws the nexrad radar
//
void NexradWidget::paintEvent([[maybe_unused]] QPaintEvent * e) {
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, false);
    painter.setWindow(QRect(-500, -500, 1000, 1000));
    // painter.setViewport(QRect(-500, -500, 1000, 1000));
    painter.translate(nexradState.xPos, nexradState.yPos);
    painter.scale(nexradState.zoom, nexradState.zoom);
    painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter.drawRect(
        (-500 - nexradState.xPos) * (1.0 / nexradState.zoom),
        (-500 - nexradState.yPos) * (1.0 / nexradState.zoom),
        (2500 - nexradState.xPos) * (1.0 / nexradState.zoom),
        (2500 - nexradState.yPos) * (1.0 / nexradState.zoom)
    );
    levelData.radarBuffers->setToPositionZero();
    //
    // draw nexrad radar
    //
    // if (!displayHold) {
    for (auto bin = 0; bin < totalBins; bin++) {
        painter.setPen(levelData.radarBuffers->colorPens[bin]);
        painter.setBrush(levelData.radarBuffers->colorBrushes[bin]);
        painter.drawPolygon(levelData.radarBuffers->rectPoints[bin]);
    }
    //}
    //
    // highways, counties, lakes
    //
    if (nexradState.zoom > 1.0) {
        if (RadarPreferences::hwEnhExt) {
            painter.setPen(QPen(RadarPreferences::colorHwExt, RadarPreferences::hwExtLinesize / nexradState.zoom, Qt::SolidLine));
            painter.drawLines(hwExtQLines);
        }
    }
    if (nexradState.zoom > 0.5) {
        if (RadarPreferences::county) {
            painter.setPen(QPen(RadarPreferences::colorCounty, RadarPreferences::countyLinesize / nexradState.zoom, Qt::SolidLine));
            painter.drawLines(countyQLines);
        }
        if (RadarPreferences::hw) {
            painter.setPen(QPen(RadarPreferences::colorHw, RadarPreferences::hwLinesize / nexradState.zoom, Qt::SolidLine));
            painter.drawLines(hwQLines);
        }
        if (RadarPreferences::lakes) {
            painter.setPen(QPen(RadarPreferences::colorLakes, RadarPreferences::lakeLinesize / nexradState.zoom, Qt::SolidLine));
            painter.drawLines(lakesQLines);
        }
    }
    //
    // statelines, optionally Canada, Mexico borders
    //
    painter.setPen(QPen(RadarPreferences::colorState, RadarPreferences::stateLinesize / nexradState.zoom, Qt::SolidLine));
    painter.drawLines(stateQLines);
    // painter.drawLines(stateQLines.data(), RadarGeometry::stateRelativeBuffer->getCapacity() / 16);

    if (RadarPreferences::caBorders) {
        painter.setPen(QPen(RadarPreferences::colorState, RadarPreferences::stateLinesize / nexradState.zoom, Qt::SolidLine));
        painter.drawLines(caQLines);
    }
    if (RadarPreferences::mxBorders) {
        painter.setPen(QPen(RadarPreferences::colorState, RadarPreferences::stateLinesize / nexradState.zoom, Qt::SolidLine));
        painter.drawLines(mxQLines);
    }
    if (ObjectPolygonWarning::areAnyEnabled()) {
        for (const PolygonType& polygonGenericType : ObjectPolygonWarning::polygonList) {
            painter.setPen(QPen(polygonGenericToQColorMap[polygonGenericType], RadarPreferences::warnLinesize / nexradState.zoom, Qt::SolidLine));
            painter.drawLines(polygonGenericToBufferMap[polygonGenericType]);
        }
    }
    if (RadarPreferences::mpd) {
        painter.setPen(QPen(polygonToColorMap[PolygonType::mpd], RadarPreferences::watmcdLinesize / nexradState.zoom, Qt::SolidLine));
        painter.drawLines(polygonToBufferMap[PolygonType::mpd]);
    }
    if (RadarPreferences::mcd) {
        painter.setPen(QPen(polygonToColorMap[PolygonType::mcd], RadarPreferences::watmcdLinesize / nexradState.zoom, Qt::SolidLine));
        painter.drawLines(polygonToBufferMap[PolygonType::mcd]);
    }
    if (RadarPreferences::watch) {
        painter.setPen(QPen(polygonToColorMap[PolygonType::watch], RadarPreferences::watmcdLinesize / nexradState.zoom, Qt::SolidLine));
        painter.drawLines(polygonToBufferMap[PolygonType::watch]);
        painter.setPen(QPen(polygonToColorMap[PolygonType::watchTornado], RadarPreferences::watmcdLinesize / nexradState.zoom, Qt::SolidLine));
        painter.drawLines(polygonToBufferMap[PolygonType::watchTornado]);
    }
    if (RadarPreferences::swo) {
        for (int i = 0; i < UtilitySwoDay1::threatList.size(); i++) {
            if (UtilitySwoDay1::hashSwo.contains(i) && swoLinesMap.contains(i)) {
                painter.setPen(QPen(UtilitySwoDay1::swoPaints[i], RadarPreferences::watmcdLinesize / nexradState.zoom, Qt::SolidLine));
                painter.drawLines(swoLinesMap[i]);
            }
        }
    }
    float scaledCircleSize = RadarPreferences::locdotSize / nexradState.zoom;
    float scaledCircleSizeAviaion = RadarPreferences::aviationSize / nexradState.zoom;
    if (scaledCircleSize < 1.0) {
        scaledCircleSize = 1.0;
    }
    if (scaledCircleSizeAviaion < 1.0) {
        scaledCircleSizeAviaion = 1.0;
    }
    if (RadarPreferences::locDot) {
        for (int i = 0; i < locationDotsTransformed.size(); i += 2) {
            painter.setPen(QPen(RadarPreferences::colorLocdot, scaledCircleSize, Qt::SolidLine));
            painter.setBrush(QBrush(RadarPreferences::colorLocdot, Qt::SolidPattern));
            painter.drawEllipse(locationDotsTransformed[i], locationDotsTransformed[i + 1], scaledCircleSize, scaledCircleSize);
        }
    }
    if (RadarPreferences::obsWindbarbs && windBarbCircleColors.size() > 0) {
        painter.setPen(QPen(Qt::red, 0.3 / nexradState.zoom, Qt::SolidLine));
        painter.drawLines(wbGustLines);
        painter.setPen(QPen(Qt::white, 0.7 / nexradState.zoom, Qt::SolidLine));
        painter.drawLines(wbLines);
        int index = 0;
        for (const QVector<float>& marker : windBarbCirclesTransformed) {
            painter.setPen(QPen(windBarbCircleColors[index], scaledCircleSizeAviaion, Qt::SolidLine));
            painter.setBrush(QBrush(windBarbCircleColors[index], Qt::SolidPattern));
            painter.drawEllipse(marker[0], marker[1], scaledCircleSizeAviaion, scaledCircleSizeAviaion);
            index += 1;
        }
    }
    //
    // Spotters
    //
    if (RadarPreferences::spotters && spotterCirclesTransformed.size() > 0) {
        for (const QVector<float>& marker : spotterCirclesTransformed) {
            painter.setPen(QPen(RadarPreferences::colorSpotter, 1.0 / nexradState.zoom, Qt::SolidLine));
            painter.setBrush(QBrush(RadarPreferences::colorSpotter, Qt::SolidPattern));
            painter.drawEllipse(marker[0], marker[1], 1.0 / nexradState.zoom, 1.0 / nexradState.zoom);
            painter.setPen(QPen(Qt::white, 0.5 / nexradState.zoom, Qt::SolidLine));
        }
    }
    //
    // Storm tracks
    //
    if (RadarPreferences::sti) {
        painter.setPen(QPen(Qt::white, RadarPreferences::watmcdLinesize / nexradState.zoom, Qt::SolidLine));
        painter.drawLines(stormTrackLines);
    }
    //
    // Hail Index
    //
    if (RadarPreferences::hi) {
        for (const auto& poly : hiPolygons) {
            painter.setPen(QPen(Qt::green, 1.0 / nexradState.zoom, Qt::SolidLine));
            painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
            painter.drawPolygon(poly);
        }
    }
    //
    // TVS
    //
    if (RadarPreferences::tvs) {
        for (const auto& poly : tvsPolygons) {
            painter.setPen(QPen(Qt::red, 1.0 / nexradState.zoom, Qt::SolidLine));
            painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
            painter.drawPolygon(poly);
        }
    }
    //
    // WPC Fronts
    //
    if (RadarPreferences::showWpcFronts && nexradState.zoom < 0.5) {
        for (const auto& front : UtilityWpcFronts::fronts) {
            painter.setPen(QPen(front.penColor, RadarPreferences::watmcdLinesize / nexradState.zoom, Qt::SolidLine));
            if (front.qLines.size() > 1 && front.qLines.size() < 500) {
                painter.drawLines(front.qLines);
            }
        }
        QFont qfont = painter.font();
        qfont.setPixelSize(static_cast<int>(TextViewMetal::fontSize / nexradState.zoom));
        painter.setFont(qfont);
        for (const TextViewMetal& item : nexradState.pressureCenterLabelsRed) {
            painter.setPen(Qt::red);
            painter.drawText(item.xPos, item.yPos, item.text);
        }
        for (const TextViewMetal& item : nexradState.pressureCenterLabelsBlue) {
            painter.setPen(Qt::blue);
            painter.drawText(item.xPos, item.yPos, item.text);
        }
    }
    //
    // Text labels - counties
    //
    if (RadarPreferences::countyLabels && nexradState.zoom > 0.5) {
        auto qfont = painter.font();
        qfont.setPixelSize(static_cast<int>(TextViewMetal::fontSize / nexradState.zoom));
        painter.setFont(qfont);
        painter.setPen(RadarPreferences::colorCountyLabels);
        for (const TextViewMetal& county : nexradState.countyLabels) {
            painter.drawText(county.xPos, county.yPos, county.text);
        }
    }
    //
    // Text labels - cities
    //
    if (RadarPreferences::cities && nexradState.zoom > 0.5) {
        auto qfont = painter.font();
        qfont.setPixelSize(static_cast<int>(TextViewMetal::fontSize / nexradState.zoom));
        painter.setFont(qfont);
        painter.setPen(RadarPreferences::colorCity);
        for (const auto& city : nexradState.cities) {
            painter.drawText(city.xPos, city.yPos, city.text);
        }
    }
    //
    // Text labels - observations
    //
    if (RadarPreferences::obs && nexradState.zoom > 0.5) {
        auto qfont = painter.font();
        qfont.setPixelSize(static_cast<int>(TextViewMetal::fontSize / nexradState.zoom));
        painter.setFont(qfont);
        for (const auto& item : nexradState.observations) {
            painter.setPen(Qt::white);
            painter.drawText(item.xPos, item.yPos, item.text);
        }
    }
    //
    // Text labels - spotters
    //
    if (RadarPreferences::spotterLabels && nexradState.zoom > 0.5) {
        auto qfont = painter.font();
        qfont.setPixelSize(static_cast<int>(TextViewMetal::fontSize / nexradState.zoom));
        painter.setFont(qfont);
        for (const auto& item : nexradState.spotterLabels) {
            painter.setPen(RadarPreferences::colorSpotter);
            painter.drawText(item.xPos, item.yPos, item.text);
        }
    }
    if (RadarPreferences::colorLegend) {
        colorMap->paintEvent(painter, nexradState.zoom, nexradState.xPos);
    }
}

NexradWidget::~NexradWidget() {
}

void NexradWidget::initColorLegend() {
    colorMap = std::unique_ptr<UIColorLegend>(new UIColorLegend(nexradState.radarProduct));
}

void NexradWidget::initializeGeomBuffers() {
    if (stateQLines.size() == 0) {
        stateQLines = QVector<QLineF>(RadarGeometry::stateRelativeBuffer->getCapacity() / 16);
    }
    if (RadarPreferences::county && countyQLines.size() == 0) {
        countyQLines = QVector<QLineF>(RadarGeometry::countyRelativeBuffer->getCapacity() / 16);
    }
    if (RadarPreferences::hw && hwQLines.size() == 0) {
        hwQLines = QVector<QLineF>(RadarGeometry::hwRelativeBuffer->getCapacity() / 16);
    }
    if (RadarPreferences::hwEnhExt && hwExtQLines.size() == 0) {
        hwExtQLines = QVector<QLineF>(RadarGeometry::hwExtRelativeBuffer->getCapacity() / 16);
    }
    if (RadarPreferences::lakes && lakesQLines.size() == 0) {
        lakesQLines = QVector<QLineF>(RadarGeometry::lakeRelativeBuffer->getCapacity() / 16);
    }
    if (RadarPreferences::caBorders && caQLines.size() == 0) {
        caQLines = QVector<QLineF>(RadarGeometry::caRelativeBuffer->getCapacity() / 16);
    }
    if (RadarPreferences::mxBorders && mxQLines.size() == 0) {
        mxQLines = QVector<QLineF>(RadarGeometry::mxRelativeBuffer->getCapacity() / 16);
    }
}

void NexradWidget::initializeGeom() {
    nexradState.pn = ProjectionNumbers(nexradState.radarSite);
    if (RadarPreferences::locDot) {
        locationDots = Location::getListLatLons();
        locationDotsTransformed.clear();
        for (const auto& latLon : locationDots) {
            //# lat lon are correct pos / neg but must match below
            auto coords = UtilityCanvasProjection::computeMercatorNumbers(latLon.lat, -1.0 * latLon.lon, nexradState.pn);
            locationDotsTransformed.append(coords);
        }
    }
    buildGeometry(stateQLines, RadarGeometry::stateRelativeBuffer);
    if (RadarPreferences::county) {
        if (countyQLines.size() == 0) {
            initializeGeomBuffers();
        }
        buildGeometry(countyQLines, RadarGeometry::countyRelativeBuffer);
    }
    if (RadarPreferences::hw) {
        if (hwQLines.size() == 0) {
            initializeGeomBuffers();
        }
        buildGeometry(hwQLines, RadarGeometry::hwRelativeBuffer);
    }
    if (RadarPreferences::hwEnhExt) {
        if (hwExtQLines.size() == 0) {
            initializeGeomBuffers();
        }
        buildGeometry(hwExtQLines, RadarGeometry::hwExtRelativeBuffer);
    }
    if (RadarPreferences::lakes) {
        if (lakesQLines.size() == 0) {
            initializeGeomBuffers();
        }
        buildGeometry(lakesQLines, RadarGeometry::lakeRelativeBuffer);
    }
    if (RadarPreferences::caBorders) {
        if (caQLines.size() == 0) {
            initializeGeomBuffers();
        }
        buildGeometry(caQLines, RadarGeometry::caRelativeBuffer);
    }
    if (RadarPreferences::mxBorders) {
        if (mxQLines.size() == 0) {
            initializeGeomBuffers();
        }
        buildGeometry(mxQLines, RadarGeometry::mxRelativeBuffer);
    }
    // buildGeomCalled = true;
    // update();
    textObject->add();
}

void NexradWidget::buildGeometry(QVector<QLineF>& qlinef, MemoryBuffer * relativeBuffer) {
    const float pnX = nexradState.pn.xDbl();
    const float pnY = nexradState.pn.yDbl();
    relativeBuffer->setPosition(0);
    for (auto index = 0; index < relativeBuffer->getCapacity() / 16; index += 1) {
        auto lat = relativeBuffer->getFloat();
        auto lon = relativeBuffer->getFloat();
        float test1 = (180.0 / M_PI * log(tan(M_PI / 4 + lat * (M_PI / 180) / 2)));
        float test2 = (180.0 / M_PI * log(tan(M_PI / 4 + pnX * (M_PI / 180) / 2)));
        const float y1 = -((test1 - test2) * nexradState.pn.oneDegreeScaleFactor) + nexradState.pn.yCenter;
        const float x1 = -((lon - pnY) * nexradState.pn.oneDegreeScaleFactor) + nexradState.pn.xCenter;
        lat = relativeBuffer->getFloat();
        lon = relativeBuffer->getFloat();
        test1 = (180.0 / M_PI * log(tan(M_PI / 4 + lat * (M_PI / 180) / 2)));
        test2 = (180.0 / M_PI * log(tan(M_PI / 4 + pnX * (M_PI / 180) / 2)));
        const float y2 = -((test1 - test2) * nexradState.pn.oneDegreeScaleFactor) + nexradState.pn.yCenter;
        const float x2 = -((lon - pnY) * nexradState.pn.oneDegreeScaleFactor) + nexradState.pn.xCenter;
        qlinef[index] = QLineF(x1, y1, x2, y2);
    }
    update();
}

void NexradWidget::wheelEvent(QWheelEvent * event) {
    if (event->angleDelta().y() > 0) {
        zoomIn();
    } else {
        zoomOut();
    }
    update();
}

void NexradWidget::mouseMoveEvent(QMouseEvent * event) {
    nexradState.xPos -= mouseStartX - event->pos().x();
    nexradState.yPos -= mouseStartY - event->pos().y();
    mouseStartX = event->pos().x();
    mouseStartY = event->pos().y();
    lastMouseType = "Drag";
    displayHold = true;
    update();
    fnPosition(nexradState.paneNumber);
}

void NexradWidget::mousePressEvent(QMouseEvent * event) {
    mouseStartX = event->pos().x();
    mouseStartY = event->pos().y();
    lastMouseType = "Click";
}

void NexradWidget::mouseDoubleClickEvent([[maybe_unused]] QMouseEvent * event) {
    lastMouseType = "Double Click";
}

void NexradWidget::performSingleClickAction() {
    if (lastMouseType == "Click") {
        message = "Click";
        zoomOut();
    }
}

void NexradWidget::mouseReleaseEvent([[maybe_unused]] QMouseEvent * event) {
    if (lastMouseType == "Drag") {
        displayHold = false;
        update();
    } else if (lastMouseType == "Click") {
        QTimer::singleShot(QApplication::doubleClickInterval(), [this]() {performSingleClickAction();});
    } else {
        message = "Double Click";
        zoomIn();
    }
}

void NexradWidget::contextMenuEvent(QContextMenuEvent * event) {
    //
    // add closest radar sites
    //
    const auto latLon = UtilityRadarUI::getLatLonFromScreenPosition(nexradState, 500.0, event->pos().x(), event->pos().y());
    const auto obsSite = UtilityMetar::findClosestObservation(latLon);
    const auto radarSites = UtilityLocation::getNearestRadarSites(latLon, 5, true);
    QVector<QAction *> actionRadarSitesList;
    QStringList actionRadarSitesNames;
    for (const auto& rid : radarSites) {
        const auto radarDescription = rid.name + ": " + Utility::getRadarSiteName(rid.name) + " (" + To::String(static_cast<int>(round(rid.distance))) + " mi)";
        actionRadarSitesList.push_back(new QAction(radarDescription, this));
        actionRadarSitesNames.push_back(rid.name);
    }
    //
    // get number of warnings
    //
    int warningCount = 0;
    for (const auto& polygonGenericType : ObjectPolygonWarning::polygonList) {
        const auto warningObject = ObjectPolygonWarning::polygonDataByType[polygonGenericType];
        if (warningObject->isEnabled) {
            warningCount += warningObject->getCount();
        }
    }
    //
    // add generic items
    //
    auto contextMenu = new QMenu(this);
    auto actionPosition = Action(latLon.latString + ", " + latLon.lonString, this);
    auto actionObservation = Action("Show Nearest Observation: " + obsSite.name + " (" + To::String(static_cast<int>(round(obsSite.distance))) + " mi)", this);
    auto actionSaveLocation = Action("Save as a location: " + latLon.printPretty(), this);
    auto actionWarnings = Action("Show Warning", this);
    auto actionWatch = Action("Show Watch text", this);
    auto actionMcd = Action("Show MCD text", this);
    auto actionMpd = Action("Show MPD text", this);
    auto actionRadarStatusMessage = Action("Show radar status message", this);

    contextMenu->addAction(actionPosition.get());
    contextMenu->addAction(actionObservation.get());
    contextMenu->addAction(actionSaveLocation.get());
    for (auto action : actionRadarSitesList) {
        contextMenu->addAction(action);
    }
    // if (ObjectPolygonWarning::areAnyEnabled() && warningCount > 0) {
    contextMenu->addAction(actionWarnings.get());
    // }
    //if (RadarPreferences::watch && MyApplication::watNoList.getValue() != "") {
        contextMenu->addAction(actionWatch.get());
    //}
    //if (RadarPreferences::mcd && MyApplication::mcdNoList.getValue() != "") {
        contextMenu->addAction(actionMcd.get());
    //}
    //if (RadarPreferences::mpd && MyApplication::mpdNoList.getValue() != "") {
        contextMenu->addAction(actionMpd.get());
    //}
    QVector<QAction *> productActions;
    QStringList productTexts;
    QStringList productList = WXGLNexrad::radarProductList;
    if (GlobalArrays::tdwrRadarCodes().contains(nexradState.radarSite)) {
        productList = WXGLNexrad::radarProductListTdwr;
    }
    //
    // radar products
    //
    for (const auto& product : productList.mid(0, 5)) {
        productTexts.push_back(product);
        productActions.push_back(new QAction(product, this));
    }
    for (auto action : productActions) {
        contextMenu->addAction(action);
    }
    contextMenu->addAction(actionRadarStatusMessage.get());
    //
    // act on selection
    //
    QAction * selectedItem = contextMenu->exec(event->globalPos());
    if (selectedItem == actionObservation.get()) {
        const auto url = GlobalVariables::tgftpSitePrefix + "/data/observations/metar/decoded/" + obsSite.name + ".TXT";
        auto window = new TextViewer(this, url, 600, 400);
        window->show();
    } else if (selectedItem == actionWarnings.get()) {
        UtilityRadarUI::showPolygonText(this, latLon);
    } else if (selectedItem == actionWatch.get()) {
        UtilityRadarUI::showNearestProduct(this, PolygonType::watch, latLon);
    } else if (selectedItem == actionMcd.get()) {
        UtilityRadarUI::showNearestProduct(this, PolygonType::mcd, latLon);
    } else if (selectedItem == actionMpd.get()) {
        UtilityRadarUI::showNearestProduct(this, PolygonType::mpd, latLon);
    } else if (selectedItem == actionRadarStatusMessage.get()) {
        auto radarStatus = UtilityRadarUI::getRadarStatusMessage(nexradState.radarSite);
        QMessageBox::about(this, "Radar status for " + nexradState.radarSite, radarStatus);
    } else if (actionRadarSitesList.contains(selectedItem)) {
        for (auto index : UtilityList::range(actionRadarSitesList.size())) {
            if (selectedItem == actionRadarSitesList[index]) {
                fnSector(nexradState.paneNumber, radarSites[index].name);
            }
        }
    } else if (productActions.contains(selectedItem)) {
        const auto product = selectedItem->text().split(":")[0];
        fnProduct(nexradState.paneNumber, product);
    } else if (selectedItem == actionSaveLocation.get()) {
        Location::save(latLon, latLon.printPretty());
    }
}

void NexradWidget::zoomIn() {
    fnZoom(1.33, nexradState.paneNumber);
}

void NexradWidget::zoomOut() {
    fnZoom(0.77, nexradState.paneNumber);
}

void NexradWidget::resizePolygons() {
    constructHi();
    constructTvs();
}

void NexradWidget::downloadDataForAnimation(int index) {
    radarBuffers = ObjectMetalRadarBuffers();
    radarBuffers.fileStorage = &fileStorage;
    levelData = WXMetalNexradLevelData(nexradState.radarProduct, &radarBuffers, To::String(nexradState.paneNumber));
    levelData.radarBuffers->animationIndex = index;
    levelData.decode();
    levelData.radarBuffers->initialize();
    totalBins = levelData.generateRadials();
    levelData.radarBuffers->setToPositionZero();
    updateStatusText();
}

void NexradWidget::constructWBLines() {
    if (RadarPreferences::obs) {
        textObject->addTextLabelsObservations();
    }
    if (RadarPreferences::obsWindbarbs) {
        windBarbCirclesTransformed.clear();
        windBarbCircleColors.clear();
        wbLines.clear();
        wbGustLines.clear();
        for (auto index : UtilityList::range(fileStorage.obsArrX.size())) {
            const auto lat = fileStorage.obsArrX[index];
            const auto lon = fileStorage.obsArrY[index];
            const auto coords = UtilityCanvasProjection::computeMercatorNumbers(lat, lon, nexradState.pn);
            const auto rawColor = fileStorage.obsArrAviationColor[index];
            const auto color = QColor(Color::red(rawColor), Color::green(rawColor), Color::blue(rawColor));
            windBarbCirclesTransformed.push_back(coords);
            windBarbCircleColors.push_back(color);
        }
        const auto wBFloats = WXGLNexradLevel3WindBarbs::decodeAndPlot(nexradState.pn, false, fileStorage);
        for (auto x : UtilityList::range3(0, wBFloats.size(), 4)) {
            wbLines.push_back(QLineF(wBFloats[x], wBFloats[x + 1], wBFloats[x + 2], wBFloats[x + 3]));
        }
        const auto wBGustFloats = WXGLNexradLevel3WindBarbs::decodeAndPlot(nexradState.pn, true, fileStorage);
        for (auto x : UtilityList::range3(0, wBGustFloats.size(), 4)) {
            wbGustLines.push_back(QLineF(wBGustFloats[x], wBGustFloats[x + 1], wBGustFloats[x + 2], wBGustFloats[x + 3]));
        }
    }
    update();
}

void NexradWidget::constructSti() {
    stormTrackLines.clear();
    const auto floats = fileStorage.stiData;
    for (auto x : UtilityList::range3(0, floats.size(), 4)) {
        stormTrackLines.push_back(QLineF(floats[x], floats[x + 1], floats[x + 2], floats[x + 3]));
    }
    update();
}

void NexradWidget::constructHi() {
    const auto floats = fileStorage.hiData;
    const float lengthOrig = 5.0;
    const float length = lengthOrig / nexradState.zoom;
    hiPolygons.clear();
    for (auto x : UtilityList::range3(0, floats.size(), 2)) {
        const auto point0 = UtilityCanvasProjection::computeMercatorNumbers(floats[x], floats[x + 1], nexradState.pn);
        const auto point1 = QPointF(point0[0], point0[1]);
        const auto point2 = QPointF(point0[0] - length, point0[1] - length);
        const auto point3 = QPointF(point0[0] + length, point0[1] - length);
        QPolygonF polygon;
        polygon.push_back(point1);
        polygon.push_back(point2);
        polygon.push_back(point3);
        hiPolygons.push_back(polygon);
    }
    update();
}

void NexradWidget::constructTvs() {
    const auto floats = fileStorage.tvsData;
    const float lengthOrig = 5.0;
    const float length = lengthOrig / nexradState.zoom;
    tvsPolygons.clear();
    for (auto x : UtilityList::range3(0, floats.size(), 2)) {
        const auto point0 = UtilityCanvasProjection::computeMercatorNumbers(floats[x], floats[x + 1], nexradState.pn);
        const auto point1 = QPointF(point0[0], point0[1]);
        const auto point2 = QPointF(point0[0] - length, point0[1] - length);
        const auto point3 = QPointF(point0[0] + length, point0[1] - length);
        QPolygonF polygon;
        polygon.push_back(point1);
        polygon.push_back(point2);
        polygon.push_back(point3);
        tvsPolygons.push_back(polygon);
    }
    update();
}

void NexradWidget::constructWpcFronts() {
    for (auto& front : UtilityWpcFronts::fronts) {
        front.translate(nexradState.pn);
    }
    textObject->addWpcPressureCenters();
    update();
}

void NexradWidget::constructSpotters() {
    spotterCirclesTransformed.clear();
    for (auto index : UtilityList::range(UtilitySpotter::lat.size())) {
        const auto lat = UtilitySpotter::lat[index];
        const auto lon = UtilitySpotter::lon[index];
        const auto coords = UtilityCanvasProjection::computeMercatorNumbers(lat, lon, nexradState.pn);
        spotterCirclesTransformed.push_back(coords);
    }
    if (RadarPreferences::spotterLabels) {
        textObject->addTextLabelsSpottersLabels();
    }
    update();
}

void NexradWidget::process(PolygonType polygonType) {
    const auto numbers = UtilityWatch::add(nexradState.pn, polygonType);
    polygonToBufferMap[polygonType] = QVector<QLineF>();
    for (auto position = 0; position < numbers.size(); position += 4) {
        polygonToBufferMap[polygonType].push_back(QLineF(numbers[position], numbers[position + 1], numbers[position + 2], numbers[position + 3]));
    }
    update();
}

void NexradWidget::processMcd() {
    process(PolygonType::mcd);
}

void NexradWidget::processMpd() {
    process(PolygonType::mpd);
}

void NexradWidget::processWatch() {
    process(PolygonType::watch);
    process(PolygonType::watchTornado);
}

void NexradWidget::processWarnings(PolygonType polygonGenericType) {
    if (ObjectPolygonWarning::areAnyEnabled()) {
        processVtec(polygonGenericType);
    }
    update();
}

void NexradWidget::constructSwo() {
    for (auto riskLevelIndex : UtilityList::range(UtilitySwoDay1::threatList.size())) {
        if (UtilitySwoDay1::hashSwo.contains(riskLevelIndex)) {
            swoLinesMap[riskLevelIndex] = QVector<QLineF>();
            for (auto x = 0; x < UtilitySwoDay1::hashSwo[riskLevelIndex].size(); x += 4) {
                const auto floatList = UtilitySwoDay1::hashSwo[riskLevelIndex];
                const auto coords1 = UtilityCanvasProjection::computeMercatorNumbers(floatList[x], floatList[x + 1], nexradState.pn);
                const auto coords2 = UtilityCanvasProjection::computeMercatorNumbers(floatList[x + 2], floatList[x + 3], nexradState.pn);
                swoLinesMap[riskLevelIndex].push_back(QLineF(coords1[0], coords1[1], coords2[0], coords2[1]));
            }
        }
    }
    update();
}

void NexradWidget::processVtec(PolygonType polygonGenericType) {
    QString warningTitle;
    const auto warningObject = ObjectPolygonWarning::polygonDataByType[polygonGenericType];
    if (warningObject->isEnabled) {
        if (warningObject->getCount() > 0) {
            warningTitle += warningObject->typeName().toUpper() + ": " + To::String(warningObject->getCount()) + " ";
        }
        const auto numbers = WXGLPolygonWarnings::addGeneric(nexradState.pn, warningObject);
        polygonGenericToBufferMap[polygonGenericType] = QVector<QLineF>();
        polygonGenericToQColorMap[polygonGenericType] = Color::intToQColor(warningObject->color());
        for (auto position = 0; position < numbers.size(); position += 4) {
            polygonGenericToBufferMap[polygonGenericType].push_back(QLineF(numbers[position], numbers[position + 1], numbers[position + 2], numbers[position + 3]));
        }
        if (!warningCountLabel.contains(polygonGenericType)) {
            // TODO FIXME
            auto label = new QLabel(this);
            label->setText(warningObject->typeName().toUpper() + ": " + To::String(warningObject->getCount()));
            // label->setStyleSheet("QLabel { background-color : white; }");
            warningCountLabel[polygonGenericType] = label;
            if (nexradState.paneNumber == 0) {
                statusBar->addWidget(label);
            }
        } else {
            warningCountLabel[polygonGenericType]->setText(warningObject->typeName().toUpper() + ": " + To::String(warningObject->getCount()));
        }
    }
    update();
}

void NexradWidget::downloadData() {
    if (GlobalArrays::tdwrRadarCodes().contains(nexradState.radarSite) && !WXGLNexrad::isProductTdwr(nexradState.radarProduct)) {
        nexradState.radarProduct = "TZL";
    } else if (GlobalArrays::nexradRadarCodes().contains(nexradState.radarSite) && WXGLNexrad::isProductTdwr(nexradState.radarProduct)) {
        nexradState.radarProduct = "N0Q";
    }
    auto tmpRadarProduct = nexradState.radarProduct;
    if (UtilityString::match(nexradState.radarProduct, "[A-Z][0-9][A-Z]")) {
        tmpRadarProduct = UtilityString::replaceRegex(nexradState.radarProduct, "([0-3])", To::String(nexradState.tiltInt));
    }
    nexradState.radarProduct = tmpRadarProduct;
    const auto isTdwr = GlobalArrays::tdwrRadarCodes().contains(nexradState.radarSite);
    const auto url = WXGLDownload::getRadarFileUrl(nexradState.radarSite, nexradState.radarProduct, isTdwr);
    // fb = new FutureBytes(this, url, [this] (const auto& ba) {
    fb = std::unique_ptr<FutureBytes>(new FutureBytes(this, url, [this] (const auto& ba) {
        fileStorage.setMemoryBuffer(QByteArray(ba));
        processDataAfterDownload();
    }));
}

void NexradWidget::processDataAfterDownload() {
    radarBuffers = ObjectMetalRadarBuffers();
    radarBuffers.fileStorage = &fileStorage;
    levelData = WXMetalNexradLevelData(nexradState.radarProduct, &radarBuffers, To::String(nexradState.paneNumber));
    levelData.radarBuffers->animationIndex = -1;
    levelData.decode();
    levelData.radarBuffers->initialize();
    totalBins = levelData.generateRadials();
    update();
    updateStatusText();
}

void NexradWidget::updateStatusText() {
    // if (UtilityTime::isRadarTimeOld(fileStorage.radarAgeMilli)) {;
    //     statusBarLabel.setStyleSheet("QLabel { background-color : yellow; }");
    // } else {
    //     statusBarLabel.setStyleSheet("QLabel { background-color : white; }");
    // }
    statusBarLabel.setText(fileStorage.radarInfo);

    auto radarAgeString = "age: " + To::String((int) (fileStorage.radarAgeMilli / 60000.0)) + " min";
    auto status = " / " + fileStorage.radarInfo.split(" ")[0];
    // auto radarAgeString = "Radar age: " + To::String(static_cast<int>(fileStorage.radarAgeMilli / 60000.0)) + " min";
    if (UtilityTime::isRadarTimeOld(fileStorage.radarAgeMilli)) {
        radarStatusBox->setOld(radarAgeString + status);
    } else {
        radarStatusBox->setCurrent(radarAgeString + status);
    }
}

void NexradWidget::changeProduct(int index) {
    nexradState.radarProduct = WXGLNexrad::radarProductList[index].split(":")[0];
    initColorLegend();
    downloadData();
}

void NexradWidget::changeSector(int index) {
    resetZoom();
    nexradState.radarSite = GlobalArrays::getRadarCodeAtIndex(index);
    initializeGeom();
    downloadData();
}

void NexradWidget::changeSector(const QString& newRadarSite) {
    resetZoom();
    nexradState.radarSite = newRadarSite;
    initializeGeom();
    downloadData();
}

void NexradWidget::resetZoom() {
    nexradState.zoom = 1.0 * 0.65;
    nexradState.xPos = 0.0;
    if (nexradState.numberOfPanes == 2) {
        nexradState.xPos = 0.0 - (originalWidth / 4.0) * nexradState.zoom;
    }
    nexradState.yPos = 0.0 - originalHeight / 3.0;
}
