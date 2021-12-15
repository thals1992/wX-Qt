// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "models/ModelViewer.h"
#include "objects/FutureBytes.h"
#include "objects/FutureVoid.h"
#include "models/ObjectModelGet.h"
#include "models/UtilityModels.h"
#include "ui/Icon.h"
#include "util/UtilityList.h"
#include "util/UtilityString.h"

ModelViewer::ModelViewer(QWidget * parent, const QString& modelType) : Window(parent) {
    this->modelType = modelType;
    setTitle("Model Viewer");
    maximize();
    boxH = HBox(this);
    box = VBox(this);
    photo = Photo(this, PhotoSizeEnum::full);

    modelObj = ObjectModel(modelType);
    modelObj.setModelVars(modelObj.model);

    comboboxModel = ComboBox(this, modelObj.models);
    comboboxModel.setIndexByValue(modelObj.model);
    comboboxModel.connect([this] { changeModelCb(); });

    comboboxRun = ComboBox(this);
    comboboxRun.addItems(modelObj.runs);
    comboboxRun.connect([this] { changeRunCb(); });

    comboboxSector = ComboBox(this, modelObj.sectors);
    comboboxSector.setIndexByValue(modelObj.sector);
    comboboxSector.connect([this] { changeSectorCb(); });

    comboboxProduct = ComboBox(this, modelObj.paramLabels);
    comboboxProduct.setIndexByValue(modelObj.param);
    comboboxProduct.connect([this] { changeProductCb(); });

    comboboxTime = ComboBox(this, modelObj.times);
    comboboxTime.connect([this] { changeTimeCb(); });

    leftButton = Button(this, Icon::Left, "Back");
    leftButton.connect([this] { moveLeftClicked(); });

    rightButton = Button(this, Icon::Right, "Forward");
    rightButton.connect([this] { moveRightClicked(); });

    boxH.addWidget(comboboxModel.get());
    boxH.addWidget(comboboxRun.get());
    boxH.addWidget(comboboxSector.get());
    boxH.addWidget(comboboxProduct.get());
    boxH.addWidget(comboboxTime.get());
    boxH.addWidget(leftButton.get());
    boxH.addWidget(rightButton.get());
    box.addLayout(boxH.get());
    box.addWidgetAndCenter(photo.get());
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
    modelObj.assignTimeIdxF(index);
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
    new FutureBytes(this, url, [this] (const auto& ba) { photo.setBytes(ba); });
}

void ModelViewer::getRun() {
    new FutureVoid(this, [this] { getRunStatus(); }, [this] { updateRunStatus(); });
}

void ModelViewer::getRunStatus() {
    ObjectModelGet::getRunStatus(modelObj);
    modelObj.run = modelObj.runTimeData.mostRecentRun;
}

void ModelViewer::updateRunStatus() {
    comboboxRun.block(0);
    comboboxTime.block(0);
    comboboxProduct.block(0);
    comboboxSector.block(0);
    if (modelObj.model == "GLCFS") {
        // pass
    } else if (modelObj.model != "SREF" && modelObj.model != "HRRR" && modelObj.model != "HREF" && modelObj.model != "ESRL") {
        for (auto index : UtilityList::range(modelObj.times.size())) {
            const auto timeStr = modelObj.times[index];
            const auto newValue = timeStr.split(" ")[0] + " " + UtilityModels::convertTimeRuntoTimeString(modelObj.runTimeData.timeStringConversion.replace("Z", ""), timeStr.split(" ")[0]);
            modelObj.setTimeArr(index, newValue);

        }
    } else if (modelObj.prefModel == "SPCHRRR" || modelObj.prefModel == "SPCSREF" || modelObj.prefModel == "ESRL") {
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
    const auto paramIndex = UtilityList::findex(modelObj.param, modelObj.params);
    comboboxProduct.setIndex(paramIndex);

    comboboxTime.setList(modelObj.times);
    comboboxTime.setIndexByValue(modelObj.getTime());

    comboboxRun.unblock(0);
    comboboxTime.unblock(0);
    comboboxProduct.unblock(0);
    comboboxSector.unblock(0);

    reload();
}
