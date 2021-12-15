// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDSTORMREPORTITEM_H
#define OBJECTCARDSTORMREPORTITEM_H

#include <QWidget>
#include "spc/StormReport.h"
#include "ui/Button.h"
#include "ui/Text.h"
#include "ui/VBox.h"

class ObjectCardStormReportItem : public VBox {
public:
    ObjectCardStormReportItem(QWidget *, const StormReport&);

private:
    void launchMap(const QString&, const QString&);
    VBox layoutButtons;
    VBox textLayout;
    Text topLine;
    Text middleLine;
    Text endLine;
    Button buttonDetails;
};

#endif  // OBJECTCARDSTORMREPORTITEM_H
