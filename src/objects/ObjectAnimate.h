// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTANIMATE_H
#define OBJECTANIMATE_H

#include <functional>
#include "objects/TimeLine.h"
#include "ui/ButtonToggle.h"
#include "ui/Photo.h"

class ObjectAnimate : public QObject {

    Q_OBJECT

public:
    ObjectAnimate();
    ObjectAnimate(
        QWidget *,
        Photo *,
        std::function<QStringList(QString, QString, int)>,
        std::function<void()>,
        ButtonToggle *);
    void stopAnimate();
    void animateClicked();
    QString product;
    QString sector;
    std::function<QStringList(QString, QString, int)> getFunction;

private:
    void loadAnimationFrame(int);
    void downloadFrames(QStringList);
    QVector<QByteArray> animationFrames;
    QWidget * parent;
    int animationSpeed;
    Photo * image;
    std::function<void()> downloadImage;
    std::function<void(int)> updateImage;
    TimeLine timeLine;
    ButtonToggle * animateButton;
};

#endif  // OBJECTANIMATE_H
