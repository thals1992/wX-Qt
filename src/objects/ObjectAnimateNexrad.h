// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTANIMATENEXRAD_H
#define OBJECTANIMATENEXRAD_H

#include "objects/TimeLine.h"
#include "ui/ButtonToggle.h"
#include "ui/ComboBox.h"
#include "radar/NexradWidget.h"

class ObjectAnimateNexrad : public QObject {

    Q_OBJECT

public:
    ObjectAnimateNexrad();
    ObjectAnimateNexrad(QWidget * parent, QVector<NexradWidget *>, ButtonToggle *, ComboBox *, ComboBox *);
    void animateClicked();
    bool isAnimating();
    void stopAnimate();
    void setAnimationSpeed();
    void setAnimationCount();

private:
    void loadAnimationFrame(int);
    void downloadFrames();
    TimeLine timeLine;
    QVector<NexradWidget *> nexradList;
    ComboBox * comboboxAnimCount;
    ComboBox * comboboxAnimSpeed;
    QWidget * parent;
    ButtonToggle * animateButton;
    int frameCount = 10;
    int animationSpeed = 2500;
};

#endif  // OBJECTANIMATENEXRAD_H
