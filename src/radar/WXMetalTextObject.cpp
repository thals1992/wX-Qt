// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/WXMetalTextObject.h"
#include "objects/WString.h"
#include "radar/PressureCenterTypeEnum.h"
#include "radar/UtilityCitiesExtended.h"
#include "radar/UtilityCountyLabels.h"
#include "radar/UtilityWpcFronts.h"
#include "settings/RadarPreferences.h"
#include "ui/TextViewMetal.h"
#include "util/To.h"
#include "util/UtilityCanvasProjection.h"
#include "util/UtilityList.h"

const float WXMetalTextObject::cityMinZoom{0.20};
const float WXMetalTextObject::obsMinZoom{0.20};
const float WXMetalTextObject::countyMinZoom{0.20};

WXMetalTextObject::WXMetalTextObject(int numPanes, NexradState& nexradState, FileStorage * fileStorage)
    : nexradState{ &nexradState }
    , numPanes{ numPanes }
    , fileStorage{ fileStorage }
    , maxCitiesPerGlview{ static_cast<size_t>(40 / numPanes) }
{
    initialize();
}

void WXMetalTextObject::addTextLabelsCitiesExtended() {
    if (RadarPreferences::cities) {
        nexradState->cities.clear();
        if (nexradState->zoom > cityMinZoom) {
            const auto cityExtLength = static_cast<int>(UtilityCitiesExtended::cities.size());
            for (auto index : range(cityExtLength)) {
                if (nexradState->cities.size() <= maxCitiesPerGlview) {
                    checkAndDrawText(
                        &nexradState->cities,
                        UtilityCitiesExtended::cities[index].latitude,
                        UtilityCitiesExtended::cities[index].longitude,
                        UtilityCitiesExtended::cities[index].name);
                }
            }
        }
    }
}

void WXMetalTextObject::checkAndDrawText(vector<TextViewMetal> * tvList, double lat, double lon, const string& text, bool checkBounds) {
    const auto latLon = UtilityCanvasProjection::computeMercatorNumbers(lat, lon, nexradState->getPn());
    const auto xPos = latLon[0];
    const auto yPos = latLon[1];
    const auto dimScale = 0.5;
    if (checkBounds && nexradState->originalWidth * -1.0 * dimScale < (xPos * nexradState->zoom) && (xPos * nexradState->zoom)  < nexradState->originalWidth * dimScale
        &&  nexradState->originalHeight * -1.0 * dimScale < (yPos * nexradState->zoom)  && (yPos * nexradState->zoom)  < nexradState->originalHeight * dimScale) {
        tvList->emplace_back();
        tvList->back().setPadding(xPos, yPos);
        tvList->back().setText(text);
    } else if (!checkBounds) {
        tvList->emplace_back();
        tvList->back().setPadding(xPos, yPos);
        tvList->back().setText(text);
    }
}

void WXMetalTextObject::initializeTextLabelsCitiesExtended() const {
    if (numPanes == 1 && RadarPreferences::cities) {
        UtilityCitiesExtended::create();
    }
}

void WXMetalTextObject::initializeTextLabelsCountyLabels() {
    if (RadarPreferences::countyLabels) {
        UtilityCountyLabels::create();
    }
}

void WXMetalTextObject::addTextLabelsCountyLabels() {
    if (RadarPreferences::countyLabels) {
        nexradState->countyLabels.clear();
        if (nexradState->zoom > countyMinZoom) {
            for (auto index : range(UtilityCountyLabels::names.size())) {
                checkAndDrawText(
                    &nexradState->countyLabels,
                    UtilityCountyLabels::location[index].lat(),
                    UtilityCountyLabels::location[index].lon(),
                    UtilityCountyLabels::names[index]);
            }
        }
    }
}

void WXMetalTextObject::initialize() {
    if (numPanes == 1) {
        initializeTextLabelsCitiesExtended();
    }
    initializeTextLabelsCountyLabels();
}

void WXMetalTextObject::add() {
    if (numPanes == 1) {
        if (RadarPreferences::cities) {
            addTextLabelsCitiesExtended();
        }
        if (RadarPreferences::countyLabels) {
            addTextLabelsCountyLabels();
        }
        if (RadarPreferences::showWpcFronts) {
            addWpcPressureCenters();
        }
        if (RadarPreferences::obs) {
            addTextLabelsObservations();
        }
    }
}

void WXMetalTextObject::addWpcPressureCenters() {
    if (RadarPreferences::showWpcFronts) {
        nexradState->pressureCenterLabelsRed.clear();
        nexradState->pressureCenterLabelsBlue.clear();
        if (nexradState->zoom < nexradState->zoomToHideMiscFeatures) {
            for (const auto& value : UtilityWpcFronts::pressureCenters) {
                if (value.centerType == LOW) {
                    checkAndDrawText(&nexradState->pressureCenterLabelsRed, value.lat, value.lon, value.pressureInMb, false);
                } else {
                    checkAndDrawText(&nexradState->pressureCenterLabelsBlue, value.lat, value.lon, value.pressureInMb, false);
                }
            }
        }
    }
}

void WXMetalTextObject::addTextLabelsObservations() {
    if (RadarPreferences::obs || RadarPreferences::obsWindbarbs) {
        nexradState->observations.clear();
        if (nexradState->zoom > obsMinZoom) {
            for (size_t index : range(fileStorage->obsArr.size())) {
                if (index < fileStorage->obsArr.size() && index < fileStorage->obsArrExt.size()) {
                    const auto tmpArrObs = WString::split(fileStorage->obsArr[index], ":");
                    const auto lat = To::Double(tmpArrObs[0]);
                    const auto lon = To::Double(tmpArrObs[1]);
                    checkAndDrawText(&nexradState->observations, lat, -1.0 * lon, tmpArrObs[2]);
                }
            }
        }
    }
}
