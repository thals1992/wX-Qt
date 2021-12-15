// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "wpc/NationalImages.h"
#include "objects/FutureBytes.h"
#include "ui/Icon.h"
#include "util/Utility.h"
#include "util/UtilityList.h"
#include "wpc/UtilityWpcImages.h"

NationalImages::NationalImages(QWidget * parent) : Window(parent) {
    setTitle("National Images");
    maximize();
    index = Utility::readPrefInt(prefToken, 0);

    box = VBox(this);
    hbox = HBox(this);
    photo = Photo(this, PhotoSizeEnum::full);

    buttonBack = Button(this, Icon::Left, "");
    buttonBack.connect([this] { moveLeftClicked(); });

    buttonForward = Button(this, Icon::Right, "");
    buttonForward.connect([this] { moveRightClicked(); });

    hbox.addWidget(buttonBack.get());
    hbox.addWidget(buttonForward.get());
    box.addLayout(hbox.get());
    box.addWidgetAndCenter(photo.get());
    box.getAndShow(this);

    int itemsSoFar = 0;
    for (auto& menu : UtilityWpcImages::titles) {
        menu.setList(UtilityWpcImages::labels, itemsSoFar);
        itemsSoFar += menu.count;
    }
    for (auto& objectMenuTitle : UtilityWpcImages::titles) {
        popoverMenus.push_back(PopoverMenu(this, objectMenuTitle.title, objectMenuTitle.get(), [this] (QString s) { changeProductByCode(s); }));
        hbox.addWidget(popoverMenus.back().get());
    }

    shortcutLeft = Shortcut(Qt::CTRL | Qt::Key_Left, this);
    shortcutLeft.connect([this] { moveLeftClicked(); });

    shortcutRight = Shortcut(Qt::CTRL | Qt::Key_Right, this);
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
    setTitle(UtilityWpcImages::labels[index]);
    new FutureBytes(this, url, [this] (const auto& ba) { photo.setBytes(ba); });
}

void NationalImages::changeProductByCode(const QString& s) {
    index = UtilityList::findex(s, UtilityWpcImages::labels);
    reload();
}
