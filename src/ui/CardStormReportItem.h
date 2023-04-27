// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDSTORMREPORTITEM_H
#define OBJECTCARDSTORMREPORTITEM_H

#include <string>
#include <QWidget>
#include "spc/StormReport.h"
#include "ui/Button.h"
#include "ui/Text.h"
#include "ui/VBox.h"

using std::string;

class CardStormReportItem : public HBox {
public:
    CardStormReportItem(QWidget *, const StormReport&);

private:
    static void launchMap(const string&, const string&);
    VBox layoutButtons;
    VBox textLayout;
    Text topLine;
    Text middleLine;
    Text endLine;
    Button buttonDetails;
};

#endif  // OBJECTCARDSTORMREPORTITEM_H
