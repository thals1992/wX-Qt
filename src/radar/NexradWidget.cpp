// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradWidget.h"
#include <QApplication>
#include <QMenu>
#include <QPainter>
#include <memory>
#include "common/GlobalArrays.h"
#include "objects/Color.h"
#include "objects/PolygonWarning.h"
#include "objects/PolygonWatch.h"
#include "objects/WString.h"
#include "radar/Nexrad.h"
#include "radar/NexradLongPressMenu.h"
#include "radar/NexradRenderUI.h"
#include "radar/SwoDayOne.h"
#include "radar/Watch.h"
#include "radar/WpcFronts.h"
#include "radar/NexradDownload.h"
#include "radar/NexradUtil.h"
#include "radar/NexradLevel3WindBarbs.h"
#include "radar/Warnings.h"
#include "settings/RadarPreferences.h"
#include "settings/UIPreferences.h"
#include "util/To.h"
#include "util/UtilityCanvasProjection.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"
#include "util/UtilityUI.h"

NexradWidget::NexradWidget(
    QWidget * parent,
    StatusBar& statusBar,
    int paneNumber,
    int numberOfPanes,
    bool useASpecificRadar,
    const string& radarToUse,
    int originalWidth,
    int originalHeight,
    const function<void(int, string)>& fnProduct,
    const function<void(int, string)>& fnSector,
    const function<void(double, int)>& fnZoom,
    const function<void(int)>& fnPosition
)
    : QWidget{parent}
    , nexradState{ NexradState{parent, paneNumber, numberOfPanes, useASpecificRadar, radarToUse, originalWidth, originalHeight} }
    , statusBarLabel{ Text{this} }
    , statusBar{ &statusBar }
    , fnProduct{ fnProduct }
    , fnSector{ fnSector }
    , fnZoom{ fnZoom }
    , fnPosition{ fnPosition }
    , levelData{ NexradLevelData{&nexradState, &fileStorage} }
    , colorLegend{ UIColorLegend{nexradState.getRadarProduct()} }
    , textObject{ NexradRenderTextObject{1, nexradState, &fileStorage} }
    , nexradDraw{ NexradDraw{ &nexradState, &fileStorage, &textObject } }
{
    setAttribute(Qt::WA_DeleteOnClose);
    nexradState.radarStatusBox->connect([this] { toggleRadar(); });
    statusBarLabel.setWordWrap(false);
    this->statusBar->addWidget(statusBarLabel);
    colorLegend.update(nexradState.getRadarProduct());
    grabGesture(Qt::TapAndHoldGesture);
    grabGesture(Qt::PinchGesture);
    show();
    nexradDraw.initGeom();
}

//
// The main method that draws the nexrad radar
//
void NexradWidget::paintEvent(QPaintEvent * event) {
    QPainter painter{this};
    painter.setPen(QPen{RadarPreferences::nexradRadarBackgroundColor, 3, Qt::SolidLine});
    painter.setBrush(QBrush{RadarPreferences::nexradRadarBackgroundColor, Qt::SolidPattern});
    painter.drawRect(event->rect());
    painter.setRenderHints(QPainter::Antialiasing, false);
    painter.setWindow(QRect{-500, -250, 1000, 1000});
    painter.translate(nexradState.xPos, nexradState.yPos);
    painter.scale(nexradState.zoom, nexradState.zoom);
    if (!hideRadar) {
        for (auto bin = 0; bin < totalBins; bin++) {
            painter.setPen(levelData.radarBuffers.colorPens[bin]);
            painter.setBrush(levelData.radarBuffers.colorBrushes[bin]);
            painter.drawPolygon(levelData.radarBuffers.rectPoints[bin]);
        }
    }
    if (nexradState.zoom > 1.0 && !hideRoads) {
        nexradDraw.drawGeomLine(painter, HwExtLines);
    }
    if (nexradState.zoom > 0.5) {
        nexradDraw.drawGeomLine(painter, CountyLines);
        if (!hideRoads) {
            nexradDraw.drawGeomLine(painter, HwLines);
        }
        nexradDraw.drawGeomLine(painter, LakeLines);
    }
    nexradDraw.drawGeomLine(painter, StateLines);
    nexradDraw.drawGeomLine(painter, CaLines);
    nexradDraw.drawGeomLine(painter, MxLines);
    drawWatch(painter);
    drawWarnings(painter);
    if (RadarPreferences::locationDot) {
        nexradDraw.drawGenericCircles(painter, RadarPreferences::locdotSize, RadarPreferences::colorLocdot, fileStorage.locationDotsTransformed);
    }
    if (RadarPreferences::sti) {
        nexradDraw.drawGenericLine(painter, RadarPreferences::stiLinesize, RadarPreferences::colorSti, stormTrackLines);
    }
    if (RadarPreferences::obsWindbarbs && !windBarbCircleColors.empty() && nexradState.zoom > 0.3) {
        nexradDraw.drawGenericLine(painter, RadarPreferences::wbLinesize, Qt::red, wbGustLines);
        nexradDraw.drawGenericLine(painter, RadarPreferences::wbLinesize, RadarPreferences::colorObsWindbarbs, wbLines);
        nexradDraw.drawWbCircles(painter, RadarPreferences::aviationSize * 2.0, windBarbCircleColors, windBarbCirclesTransformed);
    }
    if (RadarPreferences::swo) {
        drawSwo(painter);
    }
    if (RadarPreferences::showWpcFronts && nexradState.zoom < 0.5) {
        drawWpcFronts(painter);
    }
    // KEEP
    // if (RadarPreferences::locdotFollowsGps) {
    //     for (int i = 0; i < locationDotsTransformedGps.size(); i += 2) {
    //         painter.setPen(QPen(RadarPreferences::colorLocdot, 1.5 / nexradState.zoom, Qt::SolidLine));
    //         painter.setBrush(QBrush(RadarPreferences::colorLocdot, Qt::SolidPattern));
    //         QPointF center = QPointF(locationDotsTransformedGps[i], locationDotsTransformedGps[i + 1]);
    //         painter.drawEllipse(center, scaledCircleSize, scaledCircleSize);
    //     }
    //     for (int i = 0; i < locationDotsTransformedGps.size(); i += 2) {
    //         painter.setPen(QPen(RadarPreferences::colorLocdot, 1.5 / nexradState.zoom, Qt::SolidLine));
    //         painter.setBrush(QBrush(RadarPreferences::colorLocdot, Qt::NoBrush));
    //         QPointF center = QPointF(locationDotsTransformedGps[i], locationDotsTransformedGps[i + 1]);
    //         painter.drawEllipse(center, scaledCircleSize * 6.0, scaledCircleSize * 6.0);
    //     }
    // }
    if (RadarPreferences::hi) {
        nexradDraw.drawTriangles(painter, RadarPreferences::colorHi, hiPolygons);
    }
    if (RadarPreferences::tvs) {
        nexradDraw.drawTriangles(painter, Qt::red, tvsPolygons);
    }
    if (RadarPreferences::countyLabels && nexradState.zoom > 0.5) {
        nexradDraw.drawText(painter, RadarPreferences::colorCountyLabels, nexradState.countyLabels);
    }
    if (RadarPreferences::cities && nexradState.zoom > 0.5) {
        nexradDraw.drawText(painter, RadarPreferences::colorCity, nexradState.cities);
    }
    if (RadarPreferences::obs && nexradState.zoom > 0.5) {
        nexradDraw.drawText(painter, RadarPreferences::colorObs, nexradState.observations);
    }
    if (RadarPreferences::colorLegend && nexradState.zoom < 4.0) {
        colorLegend.paintEvent(painter, nexradState.zoom, nexradState.xPos, nexradState.yPos);
    }
}

void NexradWidget::drawSwo(QPainter& ctx) {
    for (auto i : range(SwoDayOne::threatList.size())) {
        if (SwoDayOne::hashSwo.find(i) != SwoDayOne::hashSwo.end() && swoLinesMap.find(i) != swoLinesMap.end()) {
            nexradDraw.drawGenericLine(ctx, RadarPreferences::swoLinesize, SwoDayOne::swoPaints[i], swoLinesMap[i]);
        }
    }
}

void NexradWidget::drawWpcFronts(QPainter& ctx) {
    for (const auto& front : WpcFronts::fronts) {
        if (front.coordinatesModified[nexradState.paneNumber].size() > 1 && front.coordinatesModified[nexradState.paneNumber].size() < 500) {
            nexradDraw.drawGenericLine(ctx, RadarPreferences::watmcdLinesize, front.penColor, front.coordinatesModified[nexradState.paneNumber]);
        }
    }
    nexradDraw.drawText(ctx, Qt::red, nexradState.pressureCenterLabelsRed);
    nexradDraw.drawText(ctx, Qt::blue, nexradState.pressureCenterLabelsBlue);
}

void NexradWidget::drawWarnings(QPainter& ctx) {
    for (const auto type1 : PolygonWarning::polygonList) {
        if (polygons.find(type1) != polygons.end() && PolygonWarning::byType[type1]->isEnabled) {
            nexradDraw.drawGenericLine(
                ctx,
                RadarPreferences::warnLinesize,
                PolygonWarning::byType[type1]->colorInt,
                polygons[type1]);
        }
    }
}

void NexradWidget::drawWatch(QPainter& ctx) {
    for (const auto type1 : PolygonWatch::polygonList) {
        if (polygons.find(type1) != polygons.end() && PolygonWatch::byType[type1]->isEnabled) {
            nexradDraw.drawGenericLine(
                ctx,
                RadarPreferences::watmcdLinesize,
                PolygonWatch::byType[type1]->colorInt,
                polygons[type1]);
        }
    }
}

// KEEP
NexradWidget::~NexradWidget() = default;

// KEEP
// void NexradWidget::updateGps(double lat, double lon) {
//    gpsX = lat;
//    gpsY = lon;
//    if (RadarPreferences::locdotFollowsGps) {
//        locationDotsTransformedGps.clear();
//        // lat lon are correct pos / neg but must match below
//        auto coords = UtilityCanvasProjection::computeMercatorNumbers(gpsX, -1.0 * gpsY, nexradState.getPn());
//        locationDotsTransformedGps.append(coords);
//    }
// }

bool NexradWidget::event(QEvent * event) {
    if (event->type() == QEvent::Gesture)
        return gestureEvent(dynamic_cast<QGestureEvent*>(event));
    return QWidget::event(event);
}

// https://doc.qt.io/qt-5/gestures-overview.html
// https://doc.qt.io/qt-5/qgestureevent.html#details
// pinch gesture for mobile
bool NexradWidget::gestureEvent(QGestureEvent * event) {
    if (auto gesture = event->gesture(Qt::TapAndHoldGesture)) {
        auto t = dynamic_cast<QTapAndHoldGesture *>(gesture);
        if (t && t->state() == Qt::GestureStarted) {
            // emit TapAndHoldStarted();
            if (UtilityUI::isMobile()) {
                const auto posF = t->position();
                const auto posGlobal = QPoint{static_cast<int>(posF.x()), static_cast<int>(posF.y())};
                const auto positionRelative = mapFromGlobal(posGlobal);
                const auto latLon = NexradRenderUI::getLatLonFromScreenPosition(nexradState, positionRelative.x(), positionRelative.y());
                NexradLongPressMenu::setupContextMenu(this, posGlobal, nexradState, latLon, fnSector, fnProduct);
            }
        } else if (t && t->state() == Qt::GestureFinished) {
            // qDebug() << "tap and hold end " << event;
            // emit TapAndHoldFinished();
        }
    }
    // https://doc.qt.io/qt-5/qtwidgets-gestures-imagegestures-example.html
    if (QGesture * pinch = event->gesture(Qt::PinchGesture)) {
        pinchTriggered(dynamic_cast<QPinchGesture *>(pinch));
    }
    // if (QGesture *swipe = event->gesture(Qt::SwipeGesture))
    //     swipeTriggered(static_cast<QSwipeGesture *>(swipe));
    // else if (QGesture *pan = event->gesture(Qt::PanGesture))
    //     panTriggered(static_cast<QPanGesture *>(pan));
    // if (QGesture *pinch = event->gesture(Qt::PinchGesture))
    //     pinchTriggered(static_cast<QPinchGesture *>(pinch));
    return true;
}

void NexradWidget::pinchTriggered(QPinchGesture *gesture) {
    QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
    if (changeFlags & QPinchGesture::RotationAngleChanged) {
        auto rotationDelta = static_cast<int>(gesture->rotationAngle() - gesture->lastRotationAngle());
        rotationAngle += rotationDelta;
        // qDebug() << "pinchTriggered(): rotate by" << rotationDelta << "->" << rotationAngle;
    }
    if (changeFlags & QPinchGesture::ScaleFactorChanged) {
        currentStepScaleFactor = static_cast<int>(gesture->totalScaleFactor());
        fnZoom(gesture->scaleFactor(), nexradState.paneNumber);
        // qDebug() << "pinchTriggered(): zoom by" << gesture->scaleFactor() << "->" << currentStepScaleFactor;
    }
    if (gesture->state() == Qt::GestureFinished) {
        scaleFactor *= currentStepScaleFactor;
        currentStepScaleFactor = 1;
    }
    update();
}

void NexradWidget::wheelEvent(QWheelEvent * event) {
    if (UIPreferences::nexradScrollWheelMotion) {
        if (event->angleDelta().y() < 0) {
            zoomIn();
        } else {
            zoomOut();
        }
    } else {
        if (event->angleDelta().y() > 0) {
            zoomIn();
        } else {
            zoomOut();
        }
    }
    update();
}

void NexradWidget::mouseMoveEvent(QMouseEvent * event) {
    nexradState.xPos -= mouseStartX - event->pos().x();
    nexradState.yPos -= mouseStartY - event->pos().y();
    mouseStartX = event->pos().x();
    mouseStartY = event->pos().y();
    lastMouseType = "Drag";
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
        zoomOut();
    }
}

void NexradWidget::mouseReleaseEvent([[maybe_unused]] QMouseEvent * event) {
    if (lastMouseType == "Drag") {
        update();
    } else if (lastMouseType == "Click") {
        QTimer::singleShot(QApplication::doubleClickInterval(), [this]() {performSingleClickAction();});
    } else {
        zoomIn();
    }
}

void NexradWidget::contextMenuEvent(QContextMenuEvent * event) {
    const auto latLon = NexradRenderUI::getLatLonFromScreenPosition(nexradState, event->pos().x(), event->pos().y());
    NexradLongPressMenu::setupContextMenu(this, event->globalPos(), nexradState, latLon, fnSector, fnProduct);
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
    levelData = nexradState.levelDataList[index];
    totalBins = levelData.totalBins;
    updateStatusBar();
}

// void NexradWidget::updateStatusBarForAnimation(int index) {
//     statusBarLabel.setText(nexradState.levelDataList[index].radarInfo);
//     const auto radarAgeString = "age: " + To::string(static_cast<int>(nexradState.levelDataList[index].radarAgeMilli / 60000.0)) + " min";
//     const auto status = " / " + WString::split(nexradState.levelDataList[index].radarInfo, " ")[0];
//     if (NexradUtil::isRadarTimeOld(nexradState.levelDataList[index].radarAgeMilli)) {
//         nexradState.radarStatusBox->setOld(radarAgeString + status);
//     } else {
//         nexradState.radarStatusBox->setCurrent(radarAgeString + status);
//     }
// }

void NexradWidget::constructWBLines() {
    if (RadarPreferences::obs) {
        textObject.addTextLabelsObservations();
    }
    if (RadarPreferences::obsWindbarbs) {
        windBarbCirclesTransformed.clear();
        windBarbCircleColors.clear();
        wbLines.clear();
        wbGustLines.clear();
        const auto wBFloats = NexradLevel3WindBarbs::decodeAndPlot(nexradState.getPn(), false, fileStorage);
        for (auto x : range3(0, wBFloats.size(), 4)) {
            wbLines.push_back(QLineF{wBFloats[x], wBFloats[x + 1], wBFloats[x + 2], wBFloats[x + 3]});
        }
        const auto wBGustFloats = NexradLevel3WindBarbs::decodeAndPlot(nexradState.getPn(), true, fileStorage);
        for (auto x : range3(0, wBGustFloats.size(), 4)) {
            wbGustLines.push_back(QLineF{wBGustFloats[x], wBGustFloats[x + 1], wBGustFloats[x + 2], wBGustFloats[x + 3]});
        }
        for (auto index : range(fileStorage.obsArrX.size())) {
            const auto rawColor = fileStorage.obsArrAviationColor[index];
            windBarbCirclesTransformed.push_back(UtilityCanvasProjection::computeMercatorNumbers(fileStorage.obsArrX[index], fileStorage.obsArrY[index], nexradState.getPn()));
            windBarbCircleColors.emplace_back(Color::red(rawColor), Color::green(rawColor), Color::blue(rawColor));
        }
    }
    update();
}

void NexradWidget::constructSti() {
    stormTrackLines.clear();
    const auto floats = fileStorage.stiData;
    for (auto x : range3(0, floats.size(), 4)) {
        stormTrackLines.push_back(QLineF{floats[x], floats[x + 1], floats[x + 2], floats[x + 3]});
    }
    update();
}

void NexradWidget::constructHi() {
    const auto floats = fileStorage.hiData;
    const auto lengthOrig = 5.0;
    const auto length = lengthOrig / nexradState.zoom;
    hiPolygons.clear();
    for (auto x : range3(0, floats.size(), 2)) {
        const auto point0 = UtilityCanvasProjection::computeMercatorNumbers(floats[x], floats[x + 1], nexradState.getPn());
        const auto point1 = QPointF{point0[0], point0[1]};
        const auto point2 = QPointF{point0[0] - length, point0[1] - length};
        const auto point3 = QPointF{point0[0] + length, point0[1] - length};
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
    const auto lengthOrig = 5.0;
    const auto length = lengthOrig / nexradState.zoom;
    tvsPolygons.clear();
    for (auto x : range3(0, floats.size(), 2)) {
        const auto point0 = UtilityCanvasProjection::computeMercatorNumbers(floats[x], floats[x + 1], nexradState.getPn());
        const auto point1 = QPointF{point0[0], point0[1]};
        const auto point2 = QPointF{point0[0] - length, point0[1] - length};
        const auto point3 = QPointF{point0[0] + length, point0[1] - length};
        QPolygonF polygon;
        polygon.push_back(point1);
        polygon.push_back(point2);
        polygon.push_back(point3);
        tvsPolygons.push_back(polygon);
    }
    update();
}

void NexradWidget::constructWpcFronts() {
    for (auto& front : WpcFronts::fronts) {
        front.translate(nexradState.paneNumber, nexradState.getPn());
    }
    textObject.addWpcPressureCenters();
    update();
}

void NexradWidget::process(PolygonType polygonType) {
    const auto numbers = Watch::add(nexradState.getPn(), polygonType);
    polygons[polygonType] = QVector<QLineF>();
    for (auto position : range3(0, numbers.size(), 4)) {
        polygons[polygonType].push_back(QLineF(numbers[position], numbers[position + 1], numbers[position + 2], numbers[position + 3]));
    }
    update();
}

void NexradWidget::processWarnings(PolygonType polygonGenericType) {
    if (PolygonWarning::areAnyEnabled()) {
        processVtec(polygonGenericType);
    }
    update();
}

void NexradWidget::constructSwo() {
    for (auto riskLevelIndex : range(SwoDayOne::threatList.size())) {
        if (SwoDayOne::hashSwo.find(riskLevelIndex) != SwoDayOne::hashSwo.end()) {
            swoLinesMap[riskLevelIndex] = QVector<QLineF>();
            for (auto x : range3(0, SwoDayOne::hashSwo[riskLevelIndex].size(), 4)) {
                const auto floatList = SwoDayOne::hashSwo[riskLevelIndex];
                const auto coords1 = UtilityCanvasProjection::computeMercatorNumbers(floatList[x], floatList[x + 1], nexradState.getPn());
                const auto coords2 = UtilityCanvasProjection::computeMercatorNumbers(floatList[x + 2], floatList[x + 3], nexradState.getPn());
                swoLinesMap[riskLevelIndex].push_back(QLineF{coords1[0], coords1[1], coords2[0], coords2[1]});
            }
        } else {
            if (swoLinesMap.find(riskLevelIndex) != swoLinesMap.end()) {
                swoLinesMap[riskLevelIndex].clear();
            }
        }
    }
    update();
}

void NexradWidget::processVtec(PolygonType polygonGenericType) {
    // string warningTitle;
    const auto warningObject = PolygonWarning::byType[polygonGenericType].get();
    if (warningObject->isEnabled) {
        // if (warningObject->getCount() > 0) {
        //     warningTitle += warningObject->typeNameUpper() + ": " + To::string(warningObject->getCount()) + " ";
        // }
        const auto numbers = Warnings::addGeneric(nexradState.getPn(), warningObject);
        polygons[polygonGenericType] = QVector<QLineF>();
        for (auto position : range3(0, numbers.size(), 4)) {
            polygons[polygonGenericType].push_back(QLineF{numbers[position], numbers[position + 1], numbers[position + 2], numbers[position + 3]});
        }
        // if (warningCountLabel.find(polygonGenericType) == warningCountLabel.end()) {
        //     auto label = new QLabel(this);
        //     label->setText(QString::fromStdString(warningObject->typeNameUpper() + ": " + To::string(warningObject->getCount())));
        //     warningCountLabel[polygonGenericType] = label;
        //     if (nexradState.paneNumber == 0) {
        //         statusBar->addWidget(label);
        //     }
        // } else {
        //     warningCountLabel[polygonGenericType]->setText(QString::fromStdString(warningObject->typeNameUpper() + ": " + To::string(warningObject->getCount())));
        // }
    }
    update();
}

void NexradWidget::downloadData() {
    if (contains(GlobalArrays::tdwrRadarCodes(), nexradState.getRadarSite()) && !NexradUtil::isProductTdwr(nexradState.getRadarProduct())) {
        nexradState.radarProduct = "TZL";
    } else if (contains(GlobalArrays::nexradRadarCodes(), nexradState.getRadarSite()) && NexradUtil::isProductTdwr(nexradState.getRadarProduct())) {
        nexradState.radarProduct = "N0Q";
    }
    auto tmpRadarProduct = nexradState.radarProduct;
    if (UtilityString::match(nexradState.getRadarProduct(), "[A-Z][0-9][A-Z]")) {
        tmpRadarProduct = UtilityString::replaceRegex1(nexradState.getRadarProduct(), "([0-3])", To::string(nexradState.tiltInt));
    }
    nexradState.radarProduct = tmpRadarProduct;
    const auto isTdwr = contains(GlobalArrays::tdwrRadarCodes(), nexradState.getRadarSite());
    const auto url = NexradDownload::getRadarFileUrl(nexradState.getRadarSite(), nexradState.getRadarProduct(), isTdwr);
    new FutureBytes{this, url, [this] (const auto& ba) {
        fileStorage.setMemoryBuffer(ba);
        processDataAfterDownload();
    }};
}

void NexradWidget::processDataAfterDownload() {
    totalBins = 0;
    levelData.radarBuffers.animationIndex = -1;
    levelData.decode();
    levelData.radarBuffers.initialize();
    levelData.generateRadials();
    totalBins = levelData.totalBins;
    update();
    updateStatusBar();
}

void NexradWidget::updateStatusBar() {
    statusBarLabel.setText(fileStorage.radarInfo);
    const auto radarAgeString = "age: " + To::string(static_cast<int>(levelData.radarAgeMilli / 60000.0)) + " min";
    const auto status = " / " + WString::split(levelData.radarInfo, " ")[0];
    if (NexradUtil::isRadarTimeOld(levelData.radarAgeMilli)) {
        nexradState.radarStatusBox->setOld(radarAgeString + status);
    } else {
        nexradState.radarStatusBox->setCurrent(radarAgeString + status);
    }
}

void NexradWidget::changeProduct(const string& product) {
    nexradState.radarProduct = WString::split(product, ":")[0];
    // FIXME TODO javafx does not do legend here
    colorLegend.update(nexradState.getRadarProduct());
    downloadData();
}

void NexradWidget::changeSector(int index) {
    nexradState.resetZoom();
    nexradState.setRadar(GlobalArrays::getRadarCodeAtIndex(index));
    nexradDraw.initGeom();
    downloadData();
}

void NexradWidget::changeSector(const string& newRadarSite) {
    nexradState.resetZoom();
    nexradState.setRadar(newRadarSite);
    nexradDraw.initGeom();
    downloadData();
}

void NexradWidget::toggleRadar() {
    toggleIndex += 1;
    if (toggleIndex == 0) {
        hideRadar = false;
        hideRoads = false;
    } else if (toggleIndex == 1) {
        hideRadar = true;
        hideRoads = false;
    } else if (toggleIndex == 2) {
        hideRadar = false;
        hideRoads = true;
    } else {
        toggleIndex = 0;
        hideRadar = false;
        hideRoads = false;
    }
    draw();
}

void NexradWidget::draw() {
    update();
}
