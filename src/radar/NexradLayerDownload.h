// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef NEXRADLAYERDOWNLOAD_H
#define NEXRADLAYERDOWNLOAD_H

#include <vector>
#include "objects/PolygonWarning.h"
#include "radar/NexradWidget.h"

using std::vector;

class NexradLayerDownload {
public:
    NexradLayerDownload(QWidget *, vector<NexradWidget *> *);
    void downloadLayers();

private:
    void updateWarnings(PolygonType);
    void processWatch(PolygonType);
    void constructWBLines(int);
    void constructSwo();
    void constructHi(int);
    void constructSti(int);
    void constructTvs(int);
    void constructWpcFronts();
    QWidget * parent;
    vector<NexradWidget *> * nexradList;
};

#endif  // NEXRADLAYERDOWNLOAD_H
