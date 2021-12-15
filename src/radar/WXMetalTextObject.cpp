// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "radar/WXMetalTextObject.h"
#include "radar/PressureCenterTypeEnum.h"
#include "radar/UtilityCitiesExtended.h"
#include "radar/UtilityCountyLabels.h"
#include "radar/UtilitySpotter.h"
#include "radar/UtilityWpcFronts.h"
#include "settings/RadarPreferences.h"
#include "ui/TextViewMetal.h"
#include "util/To.h"
#include "util/UtilityCanvasProjection.h"
#include "util/UtilityList.h"

const float WXMetalTextObject::cityMinZoom = 0.20;
const float WXMetalTextObject::obsMinZoom = 0.20;
const float WXMetalTextObject::countyMinZoom = 0.20;
const int WXMetalTextObject::textSize = 10;

WXMetalTextObject::WXMetalTextObject(int numPanes, float glViewWidth, float glViewHeight, NexradState& nexradState, float screenScale, FileStorage * fileStorage) {
    this->nexradState = &nexradState;
    this->numPanes = numPanes;
    this->glViewWidth = glViewWidth;
    this->glViewHeight = glViewHeight;
    this->fileStorage = fileStorage;
    scale = 1.0;
    fudgeFactor = 375.0;
    this->screenScale = screenScale * (glViewWidth / fudgeFactor) * 0.5;
    xFudge = 15.0 * (fudgeFactor / glViewWidth);
    yFudge = 25.0 * (fudgeFactor / glViewWidth);
    fudgeScaleFactor = 1.0;
    maxCitiesPerGlview = static_cast<int>(40 / numPanes);
    initialize();
}

void WXMetalTextObject::addTextLabelsCitiesExtended() {
    if (RadarPreferences::cities) {
        nexradState->cities.clear();
        if (nexradState->zoom > cityMinZoom) {
            const int cityExtLength = UtilityCitiesExtended::cities.size();
            for (int index : UtilityList::range(cityExtLength)) {
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

void WXMetalTextObject::checkAndDrawText(QVector<TextViewMetal> * tvList, float lat, float lon, const QString& text, bool checkBounds) {
    const auto latLon = UtilityCanvasProjection::computeMercatorNumbers(lat, lon, nexradState->pn);
    const auto xPos = latLon[0];
    const auto yPos = latLon[1];
    const auto dimScale = 0.5f;
    if (checkBounds && glViewWidth * -1.0 * dimScale < (xPos * nexradState->zoom) && (xPos * nexradState->zoom)  < glViewWidth * dimScale 
        &&  glViewHeight * -1.0 * dimScale < (yPos * nexradState->zoom)  && (yPos * nexradState->zoom)  < glViewHeight * dimScale) {
//    if (checkBounds && 0 < xPos && xPos < glViewWidth &&  0 < yPos && yPos < glViewHeight) {
//         qDebug() << xPos << yPos << glViewWidth << glViewHeight << nexradState->zoom << text;
        TextViewMetal tv = TextViewMetal();
        tv.setPadding(xPos, yPos);
        tv.setText(text);
        tvList->append(tv);
    }
}

void WXMetalTextObject::initializeTextLabelsCitiesExtended() {
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
            for (int index : UtilityList::range(UtilityCountyLabels::names.size())) {
                checkAndDrawText(
                    &nexradState->countyLabels,
                    UtilityCountyLabels::location[index].lat,
                    UtilityCountyLabels::location[index].lon,
                    UtilityCountyLabels::names[index]);
            }
        }
    }
}

void WXMetalTextObject::addTextLabelsSpottersLabels() {
    if (RadarPreferences::spotterLabels) {
        nexradState->spotterLabels.clear();
        if (nexradState->zoom > 0.5) {
            for (int index : UtilityList::range(UtilitySpotter::spotterList.size())) {
                checkAndDrawText(
                    &nexradState->spotterLabels,
                    UtilitySpotter::spotterList[index].location.lat,
                    UtilitySpotter::spotterList[index].location.lon * -1.0,
                    " " + UtilitySpotter::spotterList[index].lastName.replace("0FAV ", ""));
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
        if (RadarPreferences::spotterLabels) {
            addTextLabelsSpottersLabels();
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
            for (const PressureCenter& value : UtilityWpcFronts::pressureCenters) {
                if (value.centerType == PressureCenterTypeEnum::LOW) {
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
            for (auto index : UtilityList::range(fileStorage->obsArr.size())) {
                if (index < fileStorage->obsArr.size() && index < fileStorage->obsArrExt.size()) {
                    auto tmpArrObs = fileStorage->obsArr[index].split(":");
                    float lat = To::Float(tmpArrObs[0]);
                    float lon = To::Float(tmpArrObs[1]);
                    checkAndDrawText(&nexradState->observations, lat, -1.0 * lon, tmpArrObs[2]);
                }
            }
        }
    }
}
