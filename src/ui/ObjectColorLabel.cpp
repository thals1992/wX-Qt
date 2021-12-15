// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectColorLabel.h"
#include "objects/Color.h"
#include "ui/ColorChooser.h"

ObjectColorLabel::ObjectColorLabel(QWidget * parent, const WXColor& wxcolor) : HBox(parent) {
    this->parent = parent;
    this->wxcolor = wxcolor;
    colorPatchCurrent = ColoredBox(parent, wxcolor);
    colorPatchCurrent.get()->connect([this] { launchColorPicker(); });
    label = Text(parent, wxcolor.uiLabel);
    addWidget(colorPatchCurrent.get());
    addWidget(label.get());
}

void ObjectColorLabel::launchColorPicker() {
    auto chooser = ColorChooser(parent, &wxcolor, &colorPatchCurrent);
    chooser.run();
}
