// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UIPREFERENCES_H
#define UIPREFERENCES_H

#include <QMargins>
#include "objects/PrefBool.h"

class UIPreferences {
public:
    static void initialize();
    static const int boxPadding;
    static const int padding;
    static int mainScreenImageSize;   
    static int imageSizeNwsForecast;     
    static int imageWithTextSize;
    static int comboBoxSize;
    static QMargins textPadding;
    static QMargins zeroPadding;
    static QString homeScreenTokens;
    static bool useNwsApi;
    static bool useNwsApiForHourly;
    static bool lightningUseGoes;
    static bool nexradMainScreen;
    static bool mainScreenSevereDashboard;
    static QVector<PrefBool> homeScreenItemsImage;
    static QVector<PrefBool> homeScreenItemsText;
};

#endif  // UIPREFERENCES_H
