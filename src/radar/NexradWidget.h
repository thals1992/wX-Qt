// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NEXRADWIDGET_H
#define NEXRADWIDGET_H

#include <functional>
#include <memory>
#include <QAction>
#include <QLabel>
#include <QLineF>
#include "objects/FileStorage.h"
#include "objects/FutureBytes.h"
#include "objects/MemoryBuffer.h"
#include "objects/LatLon.h"
#include "radar/ObjectMetalRadarBuffers.h"
#include "radar/NexradState.h"
#include "radar/PolygonType.h"
#include "radar/UIColorLegend.h"
#include "radar/WXMetalNexradLevelData.h"
#include "radar/WXMetalTextObject.h"
#include "ui/RadarStatusBox.h"
#include "ui/StatusBar.h"
#include "ui/Text.h"
#include "ui/TextViewMetal.h"
#include "util/ProjectionNumbers.h"

class NexradWidget : public QWidget {
public:
    NexradWidget();
    NexradWidget(
        QWidget *,
        StatusBar&,
        RadarStatusBox *,
        int,
        int,
        bool,
        QString,
        int,
        int,
        int,
        int,
        std::function<void(int, QString)> fnProduct,
        std::function<void(int, QString)> fnSector,
        std::function<void(double, int)> fnZoom,
        std::function<void(int)> fnPosition
    );
    // std::function<void()> fnMasterDownload,
    // std::function<void(string, int)> fnSyncRadarSite,
    ~NexradWidget();
    void initializeGeom();
    void initializeGeomBuffers();
    void downloadDataForAnimation(int);
    void downloadData();
    void changeSector(const QString&);
    void changeSector(int);
    void changeProduct(int);
    void processWarnings(PolygonType);
    void processMcd();
    void processMpd();
    void processWatch();
    void constructSwo();
    void constructSpotters();
    void constructWBLines();
    void constructSti();
    void constructHi();
    void constructTvs();
    void constructWpcFronts();
    void resizePolygons();
    void initColorLegend();
    NexradState nexradState;
    FileStorage fileStorage;
    std::unique_ptr<WXMetalTextObject> textObject;
    Text statusBarLabel;

protected:
    void paintEvent(QPaintEvent *) override;
    void wheelEvent(QWheelEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void contextMenuEvent(QContextMenuEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;

private slots:
    void performSingleClickAction();

private:
    void processVtec(PolygonType);
    void processDataAfterDownload();
    void resetZoom();
    void zoomIn();
    void zoomOut();
    void buildGeometry(QVector<QLineF>&, MemoryBuffer *);
    void updateStatusText();
    void process(PolygonType);
    // FutureBytes * fb;
    std::unique_ptr<FutureBytes> fb;
    std::function<void(int, QString)> fnProduct;
    std::function<void(int, QString)> fnSector;
    std::function<void(double, int)> fnZoom;
    std::function<void(int)> fnPosition;
    int originalWidth;
    int originalHeight;
    float mouseStartX;
    float mouseStartY;
    bool displayHold = false;
    StatusBar * statusBar;
    RadarStatusBox * radarStatusBox;
    QVector<QLineF> countyQLines;
    QVector<QLineF> stateQLines;
    QVector<QLineF> hwQLines;
    QVector<QLineF> hwExtQLines;
    QVector<QLineF> lakesQLines;
    QVector<QLineF> caQLines;
    QVector<QLineF> mxQLines;
    QHash<int, QVector<QLineF>> swoLinesMap;
    ObjectMetalRadarBuffers radarBuffers;
    WXMetalNexradLevelData levelData;
    int totalBins = 0;
    QHash<PolygonType, QVector<QLineF>> polygonToBufferMap;
    QHash<PolygonType, QColor> polygonToColorMap;
    QHash<PolygonType, QVector<QLineF>> polygonGenericToBufferMap;
    QHash<PolygonType, QColor> polygonGenericToQColorMap;
    QHash<PolygonType, QLabel *> warningCountLabel;
    QVector<LatLon> locationDots;
    QVector<float> locationDotsTransformed;
    QVector<QVector<float>> windBarbCirclesTransformed;
    QVector<QColor> windBarbCircleColors;
    QVector<QVector<float>> spotterCirclesTransformed;
    QVector<QLineF> wbLines;
    QVector<QLineF> wbGustLines;
    QVector<QLineF> stormTrackLines;
    QVector<QPolygonF> hiPolygons;
    QVector<QPolygonF> tvsPolygons;
    QString lastMouseType;
    QString message;
    std::unique_ptr<UIColorLegend> colorMap;
};

#endif  // NEXRADWIDGET_H
