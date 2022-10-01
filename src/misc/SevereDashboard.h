// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SEVEREDASHBOARD_H
#define SEVEREDASHBOARD_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "misc/SevereNotice.h"
#include "misc/SevereWarning.h"
#include "radar/PolygonType.h"
#include "ui/ComboBox.h"
#include "ui/Image.h"
#include "ui/ScrolledWindow.h"
#include "ui/Shortcut.h"
#include "ui/StatusBar.h"
#include "ui/Text.h"
#include "ui/Window.h"

using std::string;
using std::unordered_map;
using std::vector;

class SevereDashboard : public Window {
public:
    explicit SevereDashboard(QWidget *);

private:
    void reload();
    void downloadWatch();
    void updateWatch();
    void updateWarnings(PolygonType);
    void launch(int);
    void updateStatusBar();
    const int imagesAcross{4};
    VBox box;
    VBox boxImages;
    ScrolledWindow sw;
    vector<HBox> boxRows;
    vector<string> urls;
    vector<Image> images;
    unordered_map<PolygonType, SevereNotice> severeNotices;
    unordered_map<PolygonType, SevereWarning> warningsByType;
    unordered_map<PolygonType, VBox> boxWarnings;
    vector<Shortcut> shortcuts;
    Shortcut shortcutReload;
};

#endif  // SEVEREDASHBOARD_H
