// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDALERTDETAILS_H
#define OBJECTCARDALERTDETAILS_H

#include <string>
#include <QWidget>
#include "misc/CapAlertXml.h"
#include "ui/Button.h"
#include "ui/ComboBox.h"
#include "ui/HBox.h"
#include "ui/Text.h"
#include "ui/VBox.h"

using std::string;

class CardAlertDetail : public HBox {
public:
    CardAlertDetail(QWidget *, const CapAlertXml&);

private:
    VBox layoutVertical;
    VBox boxText;
    Text topLine;
    Text startTimeLine;
    Text endTimeLine;
    Text middleLine;
    Button buttonDetails;
    Button buttonRadar;
};

#endif  // OBJECTCARDALERTDETAILS_H
