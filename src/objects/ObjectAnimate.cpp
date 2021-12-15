// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include <QDebug>
#include "objects/ObjectAnimate.h"
#include "objects/DownloadParallelBytes.h"
#include "util/To.h"

ObjectAnimate::ObjectAnimate() {}

ObjectAnimate::ObjectAnimate(
    QWidget * parent,
    Photo * image,
    std::function<QStringList(QString, QString, int)> getFunction,
    std::function<void()> downloadImage,
    ButtonToggle * animateButton
) : QObject(parent) {
    this->parent = parent;
    this->image = image;
    this->getFunction = getFunction;
    this->downloadImage = downloadImage;
    this->animateButton = animateButton;
    animationSpeed = 500;
    this->timeLine = TimeLine(this, animationSpeed * 20, 12, [this] (int i) {loadAnimationFrame(i); });
}

void ObjectAnimate::stopAnimate() {
    timeLine.stop();
    animateButton->setText("");
}

void ObjectAnimate::animateClicked() {
    if (timeLine.isRunning()) {
        timeLine.stop();
        animateButton->setActive(false);
        animateButton->setText("");
        downloadImage();
    } else {
        animateButton->setActive(true);
        animateButton->setText("Downloading...");
        const auto urls = getFunction(product, sector, 12);
        downloadFrames(urls);
        timeLine.setCount(urls.size());
        timeLine.start();
        animateButton->setText("Stop Animation");
    }
}

void ObjectAnimate::loadAnimationFrame(int index) {
    animateButton->setText(To::String(index + 1) + " / " + To::String(timeLine.getCount()));
    image->setFullScreen(animationFrames[index]);
}

void ObjectAnimate::downloadFrames(QStringList urls) {
    // FIXME TODO don't use new
    auto dpb = new DownloadParallelBytes(parent, urls);
    animationFrames = dpb->byteList;
}
