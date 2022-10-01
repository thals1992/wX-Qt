// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ObjectColorLabel.h"
#include "ui/ColorChooser.h"

ObjectColorLabel::ObjectColorLabel(QWidget * parent, const WXColor& wxcolor)
    : parent{ parent }
    , wxcolor{ wxcolor }
    , colorPatchCurrent{ ColoredBox{parent, wxcolor} }
    , label{ Text{parent, wxcolor.uiLabel} }
{
    colorPatchCurrent.get()->connect([this] { launchColorPicker(); });
    addWidget(colorPatchCurrent.get());
    addWidget(label.get());
}

void ObjectColorLabel::launchColorPicker() {
    auto chooser = ColorChooser{parent, &wxcolor, &colorPatchCurrent};
    chooser.run();
}
