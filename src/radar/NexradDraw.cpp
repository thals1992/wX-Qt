// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradDraw.h"
#include <QFont>
#include <QPainter>
#include <cmath>
#include <numbers>
#include "radar/RadarGeometry.h"
#include "settings/Location.h"
#include "settings/RadarPreferences.h"
#include "util/UtilityCanvasProjection.h"
#include "util/UtilityList.h"

NexradDraw::NexradDraw(NexradState * nexradState, FileStorage * fileStorage, NexradRenderTextObject * textObject)
    : nexradState{ nexradState }
    , fileStorage{ fileStorage }
    , textObject{ textObject }
{}

void NexradDraw::initGeom() {
    if (RadarPreferences::locationDot) {
        fileStorage->locationDotsTransformed.clear();
        for (const auto& latLon : Location::getListLatLons()) {
            // lat lon are correct pos / neg but must match below
            addAll(fileStorage->locationDotsTransformed, latLon.getProjection(nexradState->getPn()));
        }
    }
    // if (RadarPreferences::locdotFollowsGps) {
    //     fileStorage.locationDotsTransformedGps.clear();
    //     // lat lon are correct pos / neg but must match below
    //     addAll(fileStorage.locationDotsTransformedGps, UtilityCanvasProjection::computeMercatorNumbers(fileStorage.gpsX, -1.0 * fileStorage.gpsY, nexradState.getPn()));
    // }
    for (auto t : {
        StateLines,
        CountyLines,
        HwLines,
        HwExtLines,
        LakeLines,
        CaLines,
        MxLines,
    }) {
        convertGeomData(t);
    }
    textObject->add();
}

void NexradDraw::convertGeomData(RadarGeometryTypeEnum type) {
    if (RadarGeometry::dataByType.at(type).isEnabled) {
        if (fileStorage->relativeBuffers[type].empty()) {
            fileStorage->relativeBuffers[type] = QVector<QLineF>(RadarGeometry::dataByType.at(type).lineData.size() / 4);
        }
        const auto pnX = nexradState->getPn().x();
        const auto pnY = nexradState->getPn().y();
        const auto oneDegreeScaleFactor = nexradState->getPn().oneDegreeScaleFactor;
        const auto xCenter = nexradState->getPn().xCenter;
        const auto yCenter = nexradState->getPn().xCenter;
        auto indexBuffer = 0;
        for (auto indexRelative: range3(0, RadarGeometry::dataByType.at(type).lineData.size(), 4)) {
            auto lat = RadarGeometry::dataByType.at(type).lineData[indexRelative];
            auto lon = RadarGeometry::dataByType.at(type).lineData[indexRelative + 1];
            auto test1 =
                    180.0 / std::numbers::pi * log(tan(std::numbers::pi / 4.0 + lat * (std::numbers::pi / 180.0) / 2.0));
            auto test2 =
                    180.0 / std::numbers::pi * log(tan(std::numbers::pi / 4.0 + pnX * (std::numbers::pi / 180.0) / 2.0));
            const auto y1 = -1.0 * ((test1 - test2) * oneDegreeScaleFactor) + yCenter;
            const auto x1 = -1.0 * ((lon - pnY) * oneDegreeScaleFactor) + xCenter;
            lat = RadarGeometry::dataByType.at(type).lineData[indexRelative + 2];
            lon = RadarGeometry::dataByType.at(type).lineData[indexRelative + 3];
            test1 = 180.0 / std::numbers::pi * log(tan(std::numbers::pi / 4.0 + lat * (std::numbers::pi / 180.0) / 2.0));
            // test2 = 180.0 / std::numbers::pi * log(tan(std::numbers::pi / 4.0 + pnX * (std::numbers::pi / 180.0) / 2.0));
            const auto y2 = -1.0 * ((test1 - test2) * oneDegreeScaleFactor) + yCenter;
            const auto x2 = -1.0 * ((lon - pnY) * oneDegreeScaleFactor) + xCenter;
            fileStorage->relativeBuffers[type][indexBuffer] = QLineF(x1, y1, x2, y2);
            indexBuffer += 1;
        }
    } else {
        fileStorage->relativeBuffers[type].clear();
    }
}

void NexradDraw::drawGenericCircles(QPainter& painter, double width1, const QColor& color, const vector<double>& centers) {
    for (auto i : range3(0, static_cast<int>(centers.size()), 2)) {
        painter.setPen(QPen{color, 1.5 / nexradState->zoom, Qt::SolidLine});
        painter.setBrush(QBrush{color, Qt::SolidPattern});
        painter.drawEllipse(QRectF{centers[i], centers[i + 1], width1 * 2.0 / nexradState->zoom, width1 * 2.0 / nexradState->zoom});
    }
}

void NexradDraw::drawWbCircles(QPainter& painter, double width, const vector<QColor>& colors, const vector<vector<double>>& centers) {
    int index = 0;
    for (const auto& marker : centers) {
        painter.setPen(QPen{colors[index], 1.5 / nexradState->zoom, Qt::SolidLine});
        painter.setBrush(QBrush{colors[index], Qt::SolidPattern});
        painter.drawEllipse(QRectF{marker[0], marker[1], width / nexradState->zoom, width / nexradState->zoom});
        index += 1;
    }
}

// KEEP
// void NexradDraw::drawLocationCircle(QPainter& painter, const NexradState& nexradState, float width, const QColor& color, const QVector<float>& centers) {
//    for (int i = 0; i < centers.size(); i += 2) {
//        painter.setPen(QPen(color, 1.5 / nexradState.zoom, Qt::SolidLine));
//        painter.setBrush(QBrush(color, Qt::NoBrush));
//        QPointF center = QPointF(centers[i], centers[i + 1]);
//        painter.drawEllipse(center, width * 6.0, width * 6.0);
//    }
// }

void NexradDraw::drawGenericLine(QPainter& painter, double lineWidth, const QColor& color, const QVector<QLineF>& points) {
    if (!points.empty()) {
        painter.setPen(QPen{color, lineWidth / nexradState->zoom, Qt::SolidLine});
        painter.drawLines(points);
    }
}

void NexradDraw::drawGeomLine(QPainter& painter, RadarGeometryTypeEnum type) {
    if (RadarGeometry::dataByType.at(type).isEnabled) {
        if (!fileStorage->relativeBuffers[type].empty()) {
            painter.setPen(QPen{RadarGeometry::dataByType.at(type).qcolor,
                                RadarGeometry::dataByType.at(type).lineSize / nexradState->zoom, Qt::SolidLine});
            painter.drawLines(fileStorage->relativeBuffers[type]);
        }
    }
}

void NexradDraw::drawTriangles(QPainter& painter, const QColor& color, vector<QPolygonF>& points) {
    for (const auto& poly : points) {
        painter.setPen(QPen{color, 1.0 / nexradState->zoom, Qt::SolidLine});
        painter.setBrush(QBrush{color, Qt::SolidPattern});
        painter.drawPolygon(poly);
    }
}

void NexradDraw::drawText(QPainter& painter, const QColor& color, const vector<TextViewMetal>& textPoints) {
    QFont qfont{painter.font()};
    qfont.setPointSizeF(TextViewMetal::fontSize / nexradState->zoom);
    painter.setFont(qfont);
    painter.setPen(color);
    for (const auto& item : textPoints) {
        painter.drawText(item.xPos, item.yPos, item.text);
    }
}
