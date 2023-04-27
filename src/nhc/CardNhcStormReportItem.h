// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDNHCSTORMREPORTITEM_H
#define OBJECTCARDNHCSTORMREPORTITEM_H

#include "nhc/NhcStormDetails.h"
#include "ui/Button.h"
#include "ui/Image.h"
#include "ui/Text.h"
#include "ui/VBox.h"

class CardNhcStormReportItem : public HBox {
public:
    CardNhcStormReportItem(QWidget *, const NhcStormDetails&);

private:
    void launch();
    void launchImage();
    NhcStormDetails stormData;
    QWidget * parent;
    VBox textLayout;
    Button button;
    Image image;
    Text topLine;
    Text lastUpdateLine;
    Text startTimeLine;
    Text endTimeLine;
    Text maxWindLine;
    Text middleLine;
};

#endif  // OBJECTCARDNHCSTORMREPORTITEM_H
