// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include <QDebug>
#include <memory>
#include "objects/ObjectAnimate.h"
#include "util/To.h"

ObjectAnimate::ObjectAnimate(
    QWidget * parent,
    Photo * image,
    const function<vector<string>(string, string, int)>& getFunction,
    const function<void()>& downloadImage,
    ButtonToggle * animateButton
)
    : QObject(parent)
    , getFunction{ getFunction }
    , frameCount{ 12 }
    , parent{ parent }
    , image{ image }
    , downloadImage{ downloadImage }
    , animateButton{ animateButton }
    , animationSpeed{ 500 }
    , timeLine{ TimeLine{this, animationSpeed * 20, frameCount, [this] (int i) { loadAnimationFrame(i); }} }
{}

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
        const auto urls = getFunction(product, sector, frameCount);
        downloadFrames(urls);
        timeLine.setCount(static_cast<int>(urls.size()));
        timeLine.start();
        animateButton->setText("Stop Animation");
    }
}

void ObjectAnimate::loadAnimationFrame(int index) {
    animateButton->setText(To::string(index + 1) + " / " + To::string(timeLine.getCount()));
    image->setFullScreen(animationFrames[index]);
}

void ObjectAnimate::downloadFrames(const vector<string>& urls) {
    dpb = std::make_unique<DownloadParallelBytes>(parent, urls);
    animationFrames = dpb->byteList;
}
