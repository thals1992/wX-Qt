// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDALERTDETAILS_H
#define OBJECTCARDALERTDETAILS_H

#include <QString>
#include <QWidget>
#include "misc/CapAlertXml.h"
#include "ui/Button.h"
#include "ui/HBox.h"
#include "ui/Text.h"
#include "ui/VBox.h"

class ObjectCardAlertDetail : public HBox {
public:
    ObjectCardAlertDetail(QWidget *, CapAlertXml);

private:
    QWidget * parent;
    CapAlertXml cap;
    QString radarSite;
    VBox boxText;
    Button buttonDetails;
    Button buttonRadar;
    Text topLine;
    Text middleLine;
    Text startTimeLine;
    Text endTimeLine;
};

#endif  // OBJECTCARDALERTDETAILS_H
