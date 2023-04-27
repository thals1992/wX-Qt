// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTCARDBLACKHEADERTEXT_H
#define OBJECTCARDBLACKHEADERTEXT_H

#include <string>
#include <QWidget>
#include "ui/Text.h"
#include "ui/VBox.h"

using std::string;

class CardBlackHeaderText : public VBox {
public:
    CardBlackHeaderText(QWidget *, const string&);

private:
    Text firstRow;
};

#endif  // OBJECTCARDBLACKHEADERTEXT_H
