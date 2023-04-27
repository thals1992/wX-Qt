// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "ui/ColorLabel.h"
#include "ui/ColorChooser.h"

ColorLabel::ColorLabel(QWidget * parent, const WXColor& wxcolor)
    : parent{ parent }
    , wxcolor{ wxcolor }
    , colorPatchCurrent{ ColoredBox{parent, wxcolor} }
    , label{ Text{parent, wxcolor.uiLabel} }
{
    colorPatchCurrent.getView()->connect([this] { launchColorPicker(); });
    addWidget(colorPatchCurrent);
    addWidget(label);
}

void ColorLabel::launchColorPicker() {
    auto chooser = ColorChooser{parent, &wxcolor, &colorPatchCurrent};
    chooser.run();
}
