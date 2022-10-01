// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTANIMATENEXRAD_H
#define OBJECTANIMATENEXRAD_H

#include <vector>
#include "objects/TimeLine.h"
#include "ui/ButtonToggle.h"
#include "ui/ComboBox.h"
#include "radar/NexradWidget.h"

using std::vector;

class ObjectAnimateNexrad : public QObject {

    Q_OBJECT

public:
    ObjectAnimateNexrad(QWidget * parent, vector<NexradWidget *> *, ButtonToggle *, ComboBox *, ComboBox *);
    void animateClicked();
    void stopAnimate();
    void stopAnimateNoDownload();
    void setAnimationSpeed();
    void setAnimationCount();

private:
    void loadAnimationFrame(int);
    void downloadFrames();
    int frameCount{10};
    int animationSpeed{2500};
    QWidget * parent;
    vector<NexradWidget *> * nexradList;
    ButtonToggle * animateButton;
    ComboBox * comboboxAnimCount;
    ComboBox * comboboxAnimSpeed;
    TimeLine timeLine;
};

#endif  // OBJECTANIMATENEXRAD_H
