// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/ObjectAnimateNexrad.h"
#include "radar/WXGLDownload.h"
#include "util/To.h"
#include "util/Utility.h"
#include "util/UtilityLog.h"

ObjectAnimateNexrad::ObjectAnimateNexrad() {
}

ObjectAnimateNexrad::ObjectAnimateNexrad(QWidget * parent, QVector<NexradWidget *> nexradList, ButtonToggle * animateButton, ComboBox * comboboxAnimCount, ComboBox * comboboxAnimSpeed) {
    this->nexradList = nexradList;
    this->comboboxAnimCount = comboboxAnimCount;
    this->comboboxAnimSpeed = comboboxAnimSpeed;
    this->parent = parent;
    this->animateButton = animateButton;
    this->timeLine = TimeLine(this, animationSpeed, frameCount, [this] (int i) { loadAnimationFrame(i); });
}

void ObjectAnimateNexrad::animateClicked() {
    if (!timeLine.isRunning()) {
        animateButton->setActive(true);
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

bool ObjectAnimateNexrad::isAnimating() {
    return timeLine.isRunning();
}

void ObjectAnimateNexrad::stopAnimate() {
    // animateButton->setText("&Animate");
    animateButton->setText("");
    if (timeLine.isRunning()) {
        timeLine.stop();
        for (auto nw : nexradList) {
            nw->downloadData();
        }
    }
}

void ObjectAnimateNexrad::downloadFrames() {
    for (auto nw : nexradList) {
        WXGLDownload::getRadarFilesForAnimation(parent, frameCount, nw->nexradState.radarProduct, nw->nexradState.radarSite, &(nw->fileStorage));
    }
}

void ObjectAnimateNexrad::loadAnimationFrame(int index) {
    UtilityLog::d(To::String(index));
    for (auto nw : nexradList) {
        nw->downloadDataForAnimation(index);
    }
    animateButton->setText(To::String(index + 1) + " / " + To::String(frameCount));
    for (auto nw : nexradList) {
        nw->update();
    }
}

void ObjectAnimateNexrad::setAnimationCount() {
    Utility::writePrefInt("NEXRAD_ANIM_FRAME_COUNT2", comboboxAnimCount->getIndex());
}

void ObjectAnimateNexrad::setAnimationSpeed() {
    Utility::writePrefInt("ANIM_INTERVAL", comboboxAnimSpeed->getIndex());
}
