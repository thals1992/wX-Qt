// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/ModelViewer.h"
#include "objects/FutureBytes.h"
#include "objects/FutureVoid.h"
#include "objects/WString.h"
#include "models/ObjectModelGet.h"
#include "models/UtilityModels.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

ModelViewer::ModelViewer(QWidget * parent, const string& modelType)
    : Window{parent}
    , photo{ Photo{this, Full} }
    , modelObj{ ObjectModel{modelType} }
    , comboboxRun{ ComboBox{this} }
    , comboboxModel{ ComboBox{this, modelObj.models} }
    , comboboxSector{ ComboBox{this, modelObj.sectors} }
    , comboboxProduct{ ComboBox{this, modelObj.paramLabels} }
    , comboboxTime{ ComboBox{this, modelObj.times} }
    , leftButton{ Button{this, Left, "Back"} }
    , rightButton{ Button{this, Right, "Forward"} }
{
    setTitle("Model Viewer");
    comboboxModel.setIndexByValue(modelObj.model);
    comboboxModel.connect([this] { changeModelCb(); });

    comboboxRun.addItems(modelObj.runs);
    comboboxRun.connect([this] { changeRunCb(); });

    comboboxSector.setIndexByValue(modelObj.sector);
    comboboxSector.connect([this] { changeSectorCb(); });

    comboboxProduct.setIndexByValue(modelObj.param);
    comboboxProduct.connect([this] { changeProductCb(); });

    comboboxTime.connect([this] { changeTimeCb(); });

    leftButton.connect([this] { moveLeftClicked(); });
    rightButton.connect([this] { moveRightClicked(); });

    boxH.addWidget(comboboxModel);
    boxH.addWidget(comboboxRun);
    boxH.addWidget(comboboxSector);
    boxH.addWidget(comboboxProduct);
    boxH.addWidget(comboboxTime);
    boxH.addWidget(leftButton);
    boxH.addWidget(rightButton);
    box.addLayout(boxH);
    box.addWidgetAndCenter(photo);
    box.getAndShow(this);

    getRun();
}

void ModelViewer::changeModelCb() {
    changeModel(comboboxModel.getIndex());
}

void ModelViewer::changeRunCb() {
    changeRun(comboboxRun.getIndex());
}

void ModelViewer::changeSectorCb() {
    changeSector(comboboxSector.getIndex());
}

void ModelViewer::changeProductCb() {
    changeParam(comboboxProduct.getIndex());
}

void ModelViewer::changeTimeCb() {
    changeTime(comboboxTime.getIndex());
}

void ModelViewer::changeModel(int index) {
    modelObj.model = modelObj.models[index];
    modelObj.setModelVars(modelObj.model);
    getRun();
}

void ModelViewer::changeParam(int index) {
    modelObj.param = modelObj.params[index];
    reload();
}

void ModelViewer::changeSector(int index) {
    modelObj.sector = modelObj.sectors[index];
    reload();
}

void ModelViewer::changeRun(int index) {
    modelObj.run = modelObj.runs[index];
    reload();
}

void ModelViewer::changeTime(int index) {
    modelObj.setTimeIdx(index);
    reload();
}

void ModelViewer::moveLeftClicked() {
    modelObj.leftClick();
    comboboxTime.setIndex(modelObj.timeIdx);
    changeTime(modelObj.timeIdx);
}

void ModelViewer::moveRightClicked() {
    modelObj.rightClick();
    comboboxTime.setIndex(modelObj.timeIdx);
    changeTime(modelObj.timeIdx);
}

void ModelViewer::reload() {
    auto url = ObjectModelGet::getImageUrl(modelObj);
    modelObj.writePrefs();
    new FutureBytes{this, url, [this] (const auto& ba) { photo.setBytes(ba); }};
}

void ModelViewer::getRun() {
    new FutureVoid{this, [this] { getRunStatus(); }, [this] { updateRunStatus(); }};
}

void ModelViewer::getRunStatus() {
    ObjectModelGet::getRunStatus(modelObj);
    modelObj.run = modelObj.runTimeData.mostRecentRun;
}

void ModelViewer::updateRunStatus() {
    comboboxTime.block();
    comboboxRun.block();
    comboboxSector.block();
    comboboxProduct.block();
    comboboxModel.block();
    comboboxTime.setList(modelObj.times);
    if (modelObj.model == "GLCFS") {
        // pass
    } else if (modelObj.model != "SREF" && modelObj.model != "HRRR" && modelObj.model != "HREF" && modelObj.model != "ESRL") {
        for (auto index : range(modelObj.times.size())) {
            auto timeStr = modelObj.times[index];
            auto newValue = WString::split(timeStr, " ")[0] + " " + UtilityModels::convertTimeRuntoTimeString(WString::replace(modelObj.runTimeData.timeStringConversion, "Z", ""), WString::split(timeStr, " ")[0]);
            modelObj.setTimeArr(index, newValue);
        }
    } else if (modelObj.prefModel == "SPCHRRR" || modelObj.prefModel == "ESRL") {
        modelObj.runs = modelObj.runTimeData.listRun;
        modelObj.times = UtilityModels::updateTime(UtilityString::getLastXChars(modelObj.run, 2), modelObj.run, modelObj.times, "");
    } else {
        modelObj.runs = modelObj.runTimeData.listRun;
        modelObj.times = UtilityModels::updateTime(UtilityString::getLastXChars(modelObj.run, 3), modelObj.run, modelObj.times, "");
    }
    comboboxModel.setIndexByValue(modelObj.model);

    comboboxSector.setList(modelObj.sectors);
    comboboxSector.setIndexByValue(modelObj.sector);

    comboboxRun.setList(modelObj.runs);
    comboboxRun.setIndexByValue(modelObj.run);

    comboboxProduct.setList(modelObj.paramLabels);
    auto paramIndex = findex(modelObj.param, modelObj.params);
    comboboxProduct.setIndex(paramIndex);

    comboboxTime.setList(modelObj.times);
    comboboxTime.setIndexByValue(modelObj.getTime());

    comboboxTime.unblock();
    comboboxRun.unblock();
    comboboxSector.unblock();
    comboboxProduct.unblock();
    comboboxModel.unblock();

    reload();
}
