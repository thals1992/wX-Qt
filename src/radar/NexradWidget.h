// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NEXRADWIDGET_H
#define NEXRADWIDGET_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <QAction>
#include <QGestureEvent>
#include <QLabel>
#include <QLineF>
#include <QPinchGesture>
#include "objects/FileStorage.h"
#include "objects/FutureBytes.h"
#include "objects/MemoryBuffer.h"
#include "objects/LatLon.h"
#include "radar/NexradDraw.h"
#include "radar/NexradState.h"
#include "radar/PolygonType.h"
#include "radar/ProjectionNumbers.h"
#include "radar/UIColorLegend.h"
#include "radar/NexradLevelData.h"
#include "radar/NexradRenderTextObject.h"
#include "ui/ComboBox.h"
#include "ui/StatusBar.h"
#include "ui/Text.h"
#include "ui/TextViewMetal.h"

using std::function;
using std::string;
using std::unordered_map;
using std::vector;

class NexradWidget : public QWidget {
public:
    NexradWidget(
        QWidget *,
        StatusBar&,
        int,
        int,
        bool,
        const string&,
        int,
        int,
        const function<void(int, string)>&,
        const function<void(int, string)>&,
        const function<void(double, int)>&,
        const function<void(int)>&
    );
    ~NexradWidget() override;
//    void updateGps(double, double);
    void downloadDataForAnimation(int);
    void downloadData();
    void changeSector(const string&);
    void changeSector(int);
    void changeProduct(const string&);
    void processWarnings(PolygonType);
    void process(PolygonType);
    void constructSwo();
    void constructWBLines();
    void constructSti();
    void constructHi();
    void constructTvs();
    void constructWpcFronts();
    void resizePolygons();
    void draw();
    NexradState nexradState;
    FileStorage fileStorage;
    Text statusBarLabel;

protected:
    void paintEvent(QPaintEvent *) override;
    bool event(QEvent *) override;
    bool gestureEvent(QGestureEvent *);
    void wheelEvent(QWheelEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void contextMenuEvent(QContextMenuEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private slots:
    void performSingleClickAction();

private:
    void drawSwo(QPainter&);
    void drawWpcFronts(QPainter&);
    void drawWarnings(QPainter&);
    void drawWatch(QPainter&);
//    void drawLocationDot(wxPaintDC&) const;
//    void drawSti(wxPaintDC&) const;
//    void drawWindBarbs(wxPaintDC&);
    void pinchTriggered(QPinchGesture *);
    void processVtec(PolygonType);
    void processDataAfterDownload();
    void zoomIn();
    void zoomOut();
    void updateStatusBar();
    // void updateStatusBarForAnimation(int);
    void toggleRadar();
    double mouseStartX{};
    double mouseStartY{};
    StatusBar * statusBar;
    function<void(int, string)> fnProduct;
    function<void(int, string)> fnSector;
    function<void(double, int)> fnZoom;
    function<void(int)> fnPosition;
    unordered_map<int, QVector<QLineF>> swoLinesMap;
    NexradLevelData levelData;
    int totalBins{};
    unordered_map<PolygonType, QVector<QLineF>> polygons;
    unordered_map<PolygonType, QLabel *> warningCountLabel;
    // vector<LatLon> locationDots;
    // double gpsX{};
    // double gpsY{};
    vector<vector<double>> windBarbCirclesTransformed;
    vector<QColor> windBarbCircleColors;
    QVector<QLineF> wbLines;
    QVector<QLineF> wbGustLines;
    QVector<QLineF> stormTrackLines;
    vector<QPolygonF> hiPolygons;
    vector<QPolygonF> tvsPolygons;
    string lastMouseType;
    UIColorLegend colorLegend;
public:
    NexradRenderTextObject textObject;
    NexradDraw nexradDraw;
private:
    bool hideRadar{false};
    bool hideRoads{false};
    int toggleIndex{};
    // used by pinch zoom
    int rotationAngle{};
    int currentStepScaleFactor{};
    int scaleFactor{};
};

#endif  // NEXRADWIDGET_H
