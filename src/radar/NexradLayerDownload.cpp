// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradLayerDownload.h"
#include "objects/FutureVoid.h"
#include "objects/ObjectPolygonWatch.h"
#include "radar/PolygonType.h"
#include "radar/UtilityMetar.h"
#include "radar/UtilitySpotter.h"
#include "radar/UtilitySwoDay1.h"
#include "radar/UtilityWpcFronts.h"
#include "radar/WXGLNexradLevel3HailIndex.h"
#include "radar/WXGLNexradLevel3StormInfo.h"
#include "radar/WXGLNexradLevel3Tvs.h"
#include "settings/RadarPreferences.h"
#include "util/UtilityList.h"

NexradLayerDownload::NexradLayerDownload() {
}

NexradLayerDownload::NexradLayerDownload(QWidget * parent, QVector<NexradWidget *> nexradList) {
    this->parent = parent;
    this->nexradList = nexradList;
}

void NexradLayerDownload::downloadLayers() {
    for (auto& polygonGenericType : ObjectPolygonWarning::polygonList) {
        if (ObjectPolygonWarning::polygonDataByType[polygonGenericType]->isEnabled) {
            new FutureVoid(parent, [polygonGenericType] { ObjectPolygonWarning::polygonDataByType[polygonGenericType]->download(); }, [this, polygonGenericType] { updateWarnings(polygonGenericType); });
        }
    }
    if (RadarPreferences::mcd) {
        new FutureVoid(parent,
            [] { ObjectPolygonWatch::polygonDataByType[PolygonType::mcd]->download(); },
            [this] { processMcd(); }
        );
    }
    if (RadarPreferences::mpd) {
        new FutureVoid(parent,
            [] { ObjectPolygonWatch::polygonDataByType[PolygonType::mpd]->download(); },
            [this] { processMpd(); }
        );
    }
    if (RadarPreferences::watch) {
        new FutureVoid(parent,
            [] { ObjectPolygonWatch::polygonDataByType[PolygonType::watch]->download(); },
            [this] { processWatch(); }
        );
    }
    if (RadarPreferences::swo) {
        new FutureVoid(parent,
            [] { UtilitySwoDay1::get(); },
            [this] { constructSwo(); }
        );
    }
    // TODO FIXME support multiple frames using different radar sites for everything below
    if (RadarPreferences::obsWindbarbs || RadarPreferences::obs) {
        for (auto i : UtilityList::range(nexradList.size())) {
            new FutureVoid(parent,
                [this, i] { UtilityMetar::getStateMetarArrayForWXOGL(nexradList[i]->nexradState.radarSite, nexradList[i]->fileStorage); },
                [this, i] { constructWBLines(i); }
            );
        }
    }
    if (RadarPreferences::sti) {
        for (auto i : UtilityList::range(nexradList.size())) {
            new FutureVoid(parent,
                [this, i] { WXGLNexradLevel3StormInfo::decode(nexradList[i]->nexradState.pn, nexradList[i]->fileStorage); },
                [this, i] { constructSti(i); }
            );
        }
    }
    if (RadarPreferences::hi) {
        for (auto i : UtilityList::range(nexradList.size())) {
            new FutureVoid(parent,
                [this, i] { WXGLNexradLevel3HailIndex::decode(nexradList[i]->nexradState.pn, nexradList[i]->fileStorage); },
                [this, i] { constructHi(i); }
            );
        }
    }
    if (RadarPreferences::tvs) {
        for (auto i : UtilityList::range(nexradList.size())) {
            new FutureVoid(parent,
                [this, i] { WXGLNexradLevel3Tvs::decode(nexradList[i]->nexradState.pn, nexradList[i]->fileStorage); },
                [this, i] { constructTvs(i); }
            );
        }
    }
    if (RadarPreferences::showWpcFronts) {
        new FutureVoid(parent,
            [] { UtilityWpcFronts::get(); },
            [this] { constructWpcFronts(); }
        );
    }
    if (RadarPreferences::spotters || RadarPreferences::spotterLabels) {
        new FutureVoid(parent,
            [] { UtilitySpotter::get(); },
            [this] { constructSpotters(); }
        );
    }
}

void NexradLayerDownload::updateWarnings(PolygonType polygonGenericType) {
    for (auto nw : nexradList) {
        nw->processWarnings(polygonGenericType);
    }
}

void NexradLayerDownload::processMcd() {
    for (auto nw : nexradList) {
        nw->processMcd();
    }
}

void NexradLayerDownload::processMpd() {
    for (auto nw : nexradList) {
        nw->processMpd();
    }
}

void NexradLayerDownload::processWatch() {
    for (auto nw : nexradList) {
        nw->processWatch();
    }
}

void NexradLayerDownload::constructWBLines(int i) {
    nexradList[i]->constructWBLines();
}

void NexradLayerDownload::constructSwo() {
    for (auto nw : nexradList) {
        nw->constructSwo();
    }
}

void NexradLayerDownload::constructHi(int i) {
    nexradList[i]->constructHi();
}
void NexradLayerDownload::constructSti(int i) {
    nexradList[i]->constructSti();
}

void NexradLayerDownload::constructTvs(int i) {
    nexradList[i]->constructTvs();
}

void NexradLayerDownload::constructWpcFronts() {
    for (auto nw : nexradList) {
        nw->constructWpcFronts();
    }
}

void NexradLayerDownload::constructSpotters() {
    for (auto nw : nexradList) {
        nw->constructSpotters();
    }
}
