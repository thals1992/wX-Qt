// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef SEVEREDASHBOARD_H
#define SEVEREDASHBOARD_H

#include "misc/SevereNotice.h"
#include "misc/SevereWarning.h"
#include "radar/PolygonType.h"
#include "ui/Image.h"
#include "ui/ScrolledWindow.h"
#include "ui/StatusBar.h"
#include "ui/Text.h"
#include "ui/Window.h"

class SevereDashboard : public Window {
public:
    explicit SevereDashboard(QWidget *);

private:
    void downloadWatch();
    void updateWatch();
    void downloadWarnings(PolygonType);
    void updateWarnings(PolygonType);
    void launch(int);
    void updateStatusBar();
    int imagesAcross = 4;
    ScrolledWindow sw;
    VBox box;
    VBox boxImages;
    QVector<HBox> boxRows;
    QStringList urls;
    QVector<Image> images;
    QString warningStatusText = "";
    QString watchStatusText = "";
    QHash<PolygonType, SevereNotice> severeNotices;
    QHash<PolygonType, SevereWarning> warningsByType;
    QHash<PolygonType, VBox> boxWarnings;
};

#endif  // SEVEREDASHBOARD_H
