// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/NexradLayerDownload.h"
#include "objects/FutureVoid.h"
#include "objects/PolygonWatch.h"
#include "radar/PolygonType.h"
#include "radar/Metar.h"
#include "radar/SwoDayOne.h"
#include "radar/WpcFronts.h"
#include "radar/NexradLevel3HailIndex.h"
#include "radar/NexradLevel3StormInfo.h"
#include "radar/NexradLevel3Tvs.h"
#include "settings/RadarPreferences.h"
#include "util/UtilityList.h"

NexradLayerDownload::NexradLayerDownload(QWidget * parent, vector<NexradWidget *> * nexradList)
    : parent{ parent }
    , nexradList{ nexradList }
{}

void NexradLayerDownload::downloadLayers() {
    for (auto polygonGenericType : PolygonWarning::polygonList) {
        if (PolygonWarning::byType[polygonGenericType]->isEnabled) {
            new FutureVoid{parent, [polygonGenericType] { PolygonWarning::byType[polygonGenericType]->download(); }, [this, polygonGenericType] { updateWarnings(polygonGenericType); }};
        }
    }
    auto col1 = {Mcd, Watch, Mpd};
    for (const auto t : col1) {
        if (PolygonWatch::byType[t]->isEnabled) {
            new FutureVoid{parent,
                    [t] { PolygonWatch::byType[t]->download(); },
                    [this, t] { processWatch(t); }};
        }
    }
    if (RadarPreferences::swo) {
        new FutureVoid{parent,
            [] { SwoDayOne::get(); },
            [this] { constructSwo(); }};
    }
    // TODO FIXME support multiple frames using different radar sites for everything below
    if (RadarPreferences::obsWindbarbs || RadarPreferences::obs) {
        for (auto i : range(nexradList->size())) {
            new FutureVoid{parent,
                [this, i] { Metar::getStateMetarArrayForWXOGL((*nexradList)[i]->nexradState.getRadarSite(), (*nexradList)[i]->fileStorage); },
                [this, i] { constructWBLines(i); }};
        }
    }
    if (RadarPreferences::sti) {
        for (auto i : range(nexradList->size())) {
            new FutureVoid{parent,
                [this, i] { NexradLevel3StormInfo::decode((*nexradList)[i]->nexradState.getPn(), (*nexradList)[i]->fileStorage); },
                [this, i] { constructSti(i); }};
        }
    }
    if (RadarPreferences::hi) {
        for (auto i : range(nexradList->size())) {
            new FutureVoid{parent,
                [this, i] { NexradLevel3HailIndex::decode((*nexradList)[i]->nexradState.getPn(), (*nexradList)[i]->fileStorage); },
                [this, i] { constructHi(i); }};
        }
    }
    if (RadarPreferences::tvs) {
        for (auto i : range(nexradList->size())) {
            new FutureVoid{parent,
                [this, i] { NexradLevel3Tvs::decode((*nexradList)[i]->nexradState.getPn(), (*nexradList)[i]->fileStorage); },
                [this, i] { constructTvs(i); }};
        }
    }
    if (RadarPreferences::showWpcFronts) {
        new FutureVoid{parent,
            [] { WpcFronts::get(); },
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
