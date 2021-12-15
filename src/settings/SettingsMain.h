// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SETTINGSMAIN_H
#define SETTINGSMAIN_H

#include <functional>
#include <QScrollArea>
#include "misc/TextViewerStaticBox.h"
#include "settings/LocationEditBox.h"
#include "settings/SettingsBox.h"
#include "settings/SettingsColorsBox.h"
#include "settings/SettingsLocationsBox.h"
#include "settings/SettingsRadarBox.h"
#include "ui/ComboBox.h"
#include "ui/TabWidget.h"
#include "ui/Window.h"
#include "ui/VBox.h"

class SettingsMain : public Window {
public:
    SettingsMain(QWidget * parent, ComboBox * comboBox, std::function<void()>, bool);

protected:
    void closeEvent(QCloseEvent *) override;

private:
    QString getSettings();
    ComboBox * comboBox;
    std::function<void()> reloadFn;
    LocationEditBox * locationEditBox;
    SettingsBox * settingsBox;
    SettingsRadarBox * settingsRadarBox;
    SettingsColorsBox * settingsColorsBox;
    SettingsLocationsBox * settingsLocationsBox;
    TextViewerStaticBox * aboutBox;
    TextViewerStaticBox * shortcutsBox;
    VBox box;
    TabWidget tabWidget;
    QScrollArea * qScrollArea;
    QString settingsString;
};

#endif  // SETTINGSMAIN_H
