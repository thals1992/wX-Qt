// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef RADARSTATUSBOX_H
#define RADARSTATUSBOX_H

#include <QLabel>

class RadarStatusBox {
public:
    RadarStatusBox();
    explicit RadarStatusBox(QWidget * parent);
    void setCurrent(const QString&);
    void setOld(const QString&);
    QLabel * get();

private:
    void setText(const QString& s);
    void setBackGroundRed();
    void setBackGroundGreen();
    QLabel * label;
};

#endif  // RADARSTATUSBOX_H
