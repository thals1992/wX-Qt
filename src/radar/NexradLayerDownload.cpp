// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradLayerDownload.h"
#include "objects/FutureVoid.h"
#include "objects/ObjectPolygonWatch.h"
#include "radar/PolygonType.h"
#include "radar/UtilityMetar.h"
#include "radar/UtilitySwoDayOne.h"
#include "radar/UtilityWpcFronts.h"
#include "radar/WXGLNexradLevel3HailIndex.h"
#include "radar/WXGLNexradLevel3StormInfo.h"
#include "radar/WXGLNexradLevel3Tvs.h"
#include "settings/RadarPreferences.h"
#include "util/UtilityList.h"

NexradLayerDownload::NexradLayerDownload(QWidget * parent, vector<NexradWidget *> * nexradList)
    : parent{ parent }
    , nexradList{ nexradList }
{}

void NexradLayerDownload::downloadLayers() {
    for (auto polygonGenericType : ObjectPolygonWarning::polygonList) {
        if (ObjectPolygonWarning::polygonDataByType[polygonGenericType]->isEnabled) {
            new FutureVoid{parent, [polygonGenericType] { ObjectPolygonWarning::polygonDataByType[polygonGenericType]->download(); }, [this, polygonGenericType] { updateWarnings(polygonGenericType); }};
        }
    }
    auto col1 = {Mcd, Watch, Mpd};
    for (const auto t : col1) {
        if (ObjectPolygonWatch::polygonDataByType[t]->isEnabled) {
            new FutureVoid{parent,
                    [t] { ObjectPolygonWatch::polygonDataByType[t]->download(); },
                    [this, t] { processWatch(t); }};
        }
    }
    if (RadarPreferences::swo) {
        new FutureVoid{parent,
            [] { UtilitySwoDayOne::get(); },
            [this] { constructSwo(); }};
    }
    // TODO FIXME support multiple frames using different radar sites for everything below
    if (RadarPreferences::obsWindbarbs || RadarPreferences::obs) {
        for (auto i : range(nexradList->size())) {
            new FutureVoid{parent,
                [this, i] { UtilityMetar::getStateMetarArrayForWXOGL((*nexradList)[i]->nexradState.getRadarSite(), (*nexradList)[i]->fileStorage); },
                [this, i] { constructWBLines(i); }};
        }
    }
    if (RadarPreferences::sti) {
        for (auto i : range(nexradList->size())) {
            new FutureVoid{parent,
                [this, i] { WXGLNexradLevel3StormInfo::decode((*nexradList)[i]->nexradState.getPn(), (*nexradList)[i]->fileStorage); },
                [this, i] { constructSti(i); }};
        }
    }
    if (RadarPreferences::hi) {
        for (auto i : range(nexradList->size())) {
            new FutureVoid{parent,
                [this, i] { WXGLNexradLevel3HailIndex::decode((*nexradList)[i]->nexradState.getPn(), (*nexradList)[i]->fileStorage); },
                [this, i] { constructHi(i); }};
        }
    }
    if (RadarPreferences::tvs) {
        for (auto i : range(nexradList->size())) {
            new FutureVoid{parent,
                [this, i] { WXGLNexradLevel3Tvs::decode((*nexradList)[i]->nexradState.getPn(), (*nexradList)[i]->fileStorage); },
                [this, i] { constructTvs(i); }};
        }
    }
    if (RadarPreferences::showWpcFronts) {
        new FutureVoid{parent,
            [] { UtilityWpcFronts::get(); },
            [this] { constructWpcFronts(); }};
    }
}

void NexradLayerDownload::updateWarnings(PolygonType polygonGenericType) {
    for (auto nw : *nexradList) {
        nw->processWarnings(polygonGenericType);
    }
}

void NexradLayerDownload::processWatch(PolygonType type) {
    for (auto nw : *nexradList) {
        nw->process(type);
        if (type == Watch) {
            nw->process(WatchTornado);
        }
    }
}

void NexradLayerDownload::constructWBLines(int i) {
    (*nexradList)[i]->constructWBLines();
}

void NexradLayerDownload::constructSwo() {
    for (auto nw : *nexradList) {
        nw->constructSwo();
    }
}

void NexradLayerDownload::constructHi(int i) {
    (*nexradList)[i]->constructHi();
}

void NexradLayerDownload::constructSti(int i) {
    (*nexradList)[i]->constructSti();
}

void NexradLayerDownload::constructTvs(int i) {
    (*nexradList)[i]->constructTvs();
}

void NexradLayerDownload::constructWpcFronts() {
    for (auto nw : *nexradList) {
        nw->constructWpcFronts();
    }
}
