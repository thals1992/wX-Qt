// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTANIMATE_H
#define OBJECTANIMATE_H

#include <functional>
#include <memory>
#include <string>
#include <vector>
#include "objects/DownloadParallelBytes.h"
#include "objects/TimeLine.h"
#include "ui/ButtonToggle.h"
#include "ui/Photo.h"

using std::function;
using std::string;
using std::vector;

class ObjectAnimate : public QObject {

    Q_OBJECT

public:
    ObjectAnimate(
        QWidget *,
        Photo *,
        const function<vector<string>(string, string, int)>&,
        const function<void()>&,
        ButtonToggle *);
    void stopAnimate();
    void animateClicked();
    string product;
    string sector;
    function<vector<string>(string, string, int)> getFunction;
    int frameCount;

private:
    void loadAnimationFrame(int);
    void downloadFrames(const vector<string>&);
    QWidget * parent;
    Photo * image;
    function<void()> downloadImage;
    ButtonToggle * animateButton;
    int animationSpeed;
    TimeLine timeLine;
    vector<QByteArray> animationFrames;
    std::unique_ptr<DownloadParallelBytes> dpb;
};

#endif  // OBJECTANIMATE_H
