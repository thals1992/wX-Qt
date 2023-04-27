// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "wpc/NationalImages.h"
#include <algorithm>
#include "common/GlobalVariables.h"
#include "objects/FutureBytes.h"
#include "objects/WString.h"
#include "util/Utility.h"
#include "util/UtilityList.h"
#include "wpc/UtilityWpcImages.h"

NationalImages::NationalImages(QWidget * parent)
    : Window{parent}
    , photo{ Photo{this, Full} }
    , buttonBack{ Button{this, Left, ""} }
    , buttonForward{ Button{this, Right, ""} }
    , index{ Utility::readPrefInt(prefToken, 0) }
    , shortcutLeft{ Shortcut{Qt::CTRL | Qt::Key_Left, this} }
    , shortcutRight{ Shortcut{Qt::CTRL | Qt::Key_Right, this} }
{
    setTitle("National Images");
    buttonBack.connect([this] { moveLeftClicked(); });
    buttonForward.connect([this] { moveRightClicked(); });

    hbox.addWidget(buttonBack);
    hbox.addWidget(buttonForward);
    box.addLayout(hbox);
    box.addWidgetAndCenter(photo);
    box.getAndShow(this);

    auto itemsSoFar = 0;
    for (auto& menu : UtilityWpcImages::titles) {
        menu.setList(UtilityWpcImages::labels, itemsSoFar);
        itemsSoFar += menu.count;
    }
    for (auto& objectMenuTitle : UtilityWpcImages::titles) {
        popoverMenus.emplace_back(this, objectMenuTitle.title, objectMenuTitle.get(), [this] (const auto& s) { changeProductByCode(s); });
        hbox.addWidget(popoverMenus.back());
    }
    shortcutLeft.connect([this] { moveLeftClicked(); });
    shortcutRight.connect([this] { moveRightClicked(); });
    reload();
}

void NationalImages::moveLeftClicked() {
    index -= 1;
    index = std::max(index, 0);
    reload();
}

void NationalImages::moveRightClicked() {
    index += 1;
    index = std::min(index, static_cast<int>(UtilityWpcImages::urls.size()) - 1);
    reload();
}

void NationalImages::reload() {
    Utility::writePrefInt(prefToken, index);
    auto url = UtilityWpcImages::urls[index];
    if (WString::contains(url, GlobalVariables::nwsGraphicalWebsitePrefix + "/images/conus/")) {
        url += "1_conus.png";
    }
    setTitle(UtilityWpcImages::labels[index]);
    new FutureBytes{this, url, [this] (const auto& ba) { photo.setBytes(ba); }};
}

void NationalImages::changeProductByCode(const string& s) {
    index = findex(s, UtilityWpcImages::labels);
    reload();
}
