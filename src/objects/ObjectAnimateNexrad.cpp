// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/ObjectAnimateNexrad.h"
#include <iostream>
#include "radar/NexradDownload.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityLog.h"

ObjectAnimateNexrad::ObjectAnimateNexrad(QWidget * parent, vector<NexradWidget *> * nexradList, ButtonToggle * animateButton, ComboBox * comboboxAnimCount, ComboBox * comboboxAnimSpeed)
    : parent{ parent }
    , nexradList{ nexradList }
    , animateButton{ animateButton }
    , comboboxAnimCount{ comboboxAnimCount }
    , comboboxAnimSpeed{ comboboxAnimSpeed }
    , timeLine{ TimeLine{this, animationSpeed, frameCount, [this] (int i) { loadAnimationFrame(i); }} }
{}

void ObjectAnimateNexrad::animateClicked() {
    if (!timeLine.isRunning()) {
//        animateButton->setActive(true);
        frameCount = To::Int(comboboxAnimCount->getValue());
        animationSpeed = To::Int(comboboxAnimSpeed->getValue()) * 500;
        animateButton->setText("Downloading");
        downloadFrames();
        timeLine.setSpeed(animationSpeed);
        timeLine.setCount(frameCount);
        timeLine.start();
    } else {
        stopAnimate();
    }
}

// KEEP
// bool ObjectAnimateNexrad::isAnimating() {
//    return timeLine.isRunning();
// }

void ObjectAnimateNexrad::stopAnimate() {
    animateButton->setText("");
    for (auto nw : *nexradList) {
        nw->nexradState.levelDataList.clear();
    }
    if (timeLine.isRunning()) {
        timeLine.stop();
        for (auto nw : *nexradList) {
            nw->downloadData();
        }
    }
}

void ObjectAnimateNexrad::stopAnimateNoDownload() {
    animateButton->setText("");
    animateButton->setActive(false);
    for (auto nw : *nexradList) {
        nw->nexradState.levelDataList.clear();
    }
    if (timeLine.isRunning()) {
        timeLine.stop();
    }
}

void ObjectAnimateNexrad::downloadFrames() {
    // std::cout << "START: downloadFrames" << std::endl;
    for (auto nw : *nexradList) {
        // std::cout << "START: download" << std::endl;
        NexradDownload::getRadarFilesForAnimation(parent, frameCount, nw->nexradState.getRadarProduct(), nw->nexradState.getRadarSite(), &(nw->fileStorage));
        nw->nexradState.levelDataList.clear();
        // std::cout << "START: process" << std::endl;
        nw->nexradState.processAnimationFiles(frameCount, &(nw->fileStorage));
    }
    // std::cout << "END: downloadFrames" << std::endl;
}

void ObjectAnimateNexrad::loadAnimationFrame(int index) {
    UtilityLog::d(To::string(index));
    for (auto nw : *nexradList) {
        nw->downloadDataForAnimation(index);
    }
    animateButton->setText(To::stringPadLeftZeros(To::string(index + 1), 2) + " / " + To::string(frameCount));
    for (auto nw : *nexradList) {
        nw->update();
    }
}

void ObjectAnimateNexrad::setAnimationCount() {
    Utility::writePrefInt("NEXRAD_ANIM_FRAME_COUNT2", comboboxAnimCount->getIndex());
}

void ObjectAnimateNexrad::setAnimationSpeed() {
    Utility::writePrefInt("ANIM_INTERVAL", comboboxAnimSpeed->getIndex());
    animationSpeed = To::Int(comboboxAnimSpeed->getValue()) * 500;
    timeLine.setSpeed(animationSpeed);
}
