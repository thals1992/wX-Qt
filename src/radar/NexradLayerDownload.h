// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NEXRADLAYERDOWNLOAD_H
#define NEXRADLAYERDOWNLOAD_H

#include "objects/ObjectPolygonWarning.h"
#include "radar/NexradWidget.h"

class NexradLayerDownload {
public:
    NexradLayerDownload();
    NexradLayerDownload(QWidget *, QVector<NexradWidget *>);
    void downloadLayers();

private:
    void updateWarnings(PolygonType polygonGenericType);
    void processMcd();
    void processMpd();
    void processWatch();
    void constructWBLines(int);
    void constructSwo();
    void constructHi(int);
    void constructSti(int);
    void constructTvs(int);
    void constructWpcFronts();
    void constructSpotters();
    QVector<NexradWidget *> nexradList;
    QWidget * parent;
};

#endif  // NEXRADLAYERDOWNLOAD_H
