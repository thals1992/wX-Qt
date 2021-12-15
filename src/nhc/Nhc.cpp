// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "nhc/Nhc.h"
#include "objects/FutureBytes.h"
#include "nhc/NhcOceanEnum.h"
#include "nhc/ObjectNhcRegionSummary.h"
#include "util/UtilityList.h"

Nhc::Nhc(QWidget * parent) : Window(parent) {
    setTitle("NHC");
    maximize();
    boxText = VBox(this);
    box = VBox(this);
    objectNhc = ObjectNhc();
    objectNhc.getTextData();
    objectNhc.showTextData();
    for (const auto& storm : objectNhc.stormDataList) {
        stormCards.push_back(new ObjectCardNhcStormReportItem(this, storm));
        boxText.addLayout(stormCards.back()->get());
    }
    for (int nhcInt = ATL; nhcInt != LAST; nhcInt++ ) {
        NhcOceanEnum region = static_cast<NhcOceanEnum>(nhcInt);
        ObjectNhcRegionSummary objectNhcRegionSummary = ObjectNhcRegionSummary(region);
        urls += objectNhcRegionSummary.urls;
    }
    box.addLayout(boxText.get());
    box.addImageRows(urls, images, 3);
    sw = ScrolledWindow(this, box);
    for (auto index : UtilityList::range(urls.size())) {
        new FutureBytes(this, urls[index], [this, index] (const auto& ba) { images[index].setBytes(ba); });
    }
}
