// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "wpc/NationalText.h"
#include "objects/FutureText.h"
#include "ui/Icon.h"
#include "util/Utility.h"
#include "util/UtilityList.h"
#include "wpc/UtilityWpcText.h"

NationalText::NationalText(QWidget * parent, const QString& productF): Window(parent) {
    setTitle("National Text Products");
    maximize();
    if (productF != "") {
        product = product.toLower();
        savePref = false;
    } else {
        product = Utility::readPref(prefTokenProduct, product);
    }

    text = Text(this);
    box = VBox(this);
    hbox = HBox(this);

    buttonBack = Button(this, Icon::Left, "");
    buttonBack.connect([this] { moveLeftClicked(); });

    buttonForward = Button(this, Icon::Right, "");
    buttonForward.connect([this] { moveRightClicked(); });

    hbox.addWidget(buttonBack.get());
    hbox.addWidget(buttonForward.get());
    box.addLayout(hbox.get());
    box.addWidgetAndCenterTop(text.get());
    box.addStretch();
    sw = ScrolledWindow(this, box);

    int itemsSoFar = 0;
    for (auto& menu : UtilityWpcText::titles) {
        menu.setList(UtilityWpcText::labels, itemsSoFar);
        itemsSoFar += menu.count;
    }
    for (auto& objectMenuTitle : UtilityWpcText::titles) {
        popoverMenus.push_back(PopoverMenu(this, objectMenuTitle.title, objectMenuTitle.get(), [this] (const auto& s) { changeProductByCode(s); }));
        hbox.addWidget(popoverMenus.back().get());
    }

    shortcutLeft = Shortcut(Qt::CTRL | Qt::Key_Left, this);
    shortcutLeft.connect([this] { moveLeftClicked(); });

    shortcutRight = Shortcut(Qt::CTRL | Qt::Key_Right, this);
    shortcutRight.connect([this] { moveRightClicked(); });

    reload();
}

void NationalText::moveLeftClicked() {
    index -= 1;
    index = std::max(index, 0);
    product = UtilityWpcText::labels[index].split(":")[0];
    reload();
}

void NationalText::moveRightClicked() {
    index += 1;
    index = std::min(index, static_cast<int>(UtilityWpcText::labels.size()) - 1);
    product = UtilityWpcText::labels[index].split(":")[0];
    reload();
}

void NationalText::reload() {
    if (savePref) {
        Utility::writePref(prefTokenProduct, product);
    }
    index = UtilityList::findex(product, UtilityWpcText::labels);
    setTitle(UtilityWpcText::labels[index]);
    new FutureText(this, product.toUpper(), [this] (const auto& s) { text.setText(s); });
}

void NationalText::changeProductByCode(const QString& s) {
    product = s.split(":")[0];
    reload();
}
