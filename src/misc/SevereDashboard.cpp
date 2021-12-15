// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/SevereDashboard.h"
#include <QByteArray>
#include "objects/FutureVoid.h"
#include "objects/FutureBytes.h"
#include "objects/ObjectPolygonWatch.h"
#include "spc/SpcMcdWatchMpdViewer.h"
#include "spc/SpcStormReports.h"
#include "misc/UsAlerts.h"
#include "ui/ObjectCardBlackHeaderText.h"
#include "ui/ObjectCardDashAlertItem.h"
#include "ui/ObjectDividerLine.h"
#include "util/UtilityDownload.h"
#include "util/UtilityList.h"

SevereDashboard::SevereDashboard(QWidget * parent) : Window(parent) {
    setTitle("Severe Dashboard");
    maximize();
    box = VBox(this);
    boxImages = VBox(this);

    severeNotices[PolygonType::watch] = SevereNotice(PolygonType::watch);
    severeNotices[PolygonType::mcd] = SevereNotice(PolygonType::mcd);
    severeNotices[PolygonType::mpd] = SevereNotice(PolygonType::mpd);

    warningsByType[PolygonType::tor] = SevereWarning(PolygonType::tor);
    warningsByType[PolygonType::tst] = SevereWarning(PolygonType::tst);
    warningsByType[PolygonType::ffw] = SevereWarning(PolygonType::ffw);

    boxWarnings[PolygonType::tor] = VBox();
    boxWarnings[PolygonType::tst] = VBox();
    boxWarnings[PolygonType::ffw] = VBox();

    box.addLayout(boxImages.get());
    box.addLayout(boxWarnings[PolygonType::tor].get());
    box.addLayout(boxWarnings[PolygonType::tst].get());
    box.addLayout(boxWarnings[PolygonType::ffw].get());
    sw = ScrolledWindow(this, box.get());

    for (auto& k : {PolygonType::tor, PolygonType::tst, PolygonType::ffw}) {
        new FutureVoid(this, [this, k] { downloadWarnings(k); }, [this, k] { updateWarnings(k); });
    }
    new FutureVoid(this, [this] { downloadWatch(); }, [this] { updateWatch(); });
}

void SevereDashboard::downloadWarnings(PolygonType t) {
    warningsByType[t].download();
}

void SevereDashboard::downloadWatch() {
    urls.push_back(UtilityDownload::getImageProduct("USWARN"));
    urls.push_back(UtilityDownload::getImageProduct("STRPT"));
    for (auto t : {PolygonType::mcd, PolygonType::mpd, PolygonType::watch}) {
        ObjectPolygonWatch::polygonDataByType[t]->download();
        severeNotices[t].getBitmaps();
        for (const auto& url : severeNotices[t].urls) {
            urls.push_back(url);
        }
    }
}

void SevereDashboard::updateWatch() {
    for (auto index : UtilityList::range(urls.size())) {
        images.push_back(Image::withIndex(this, index));
        images.back().setNumberAcross(imagesAcross);
    }
    for (auto index : UtilityList::range(urls.size())) {
        images[index].connect([this, index] { return launch(index); });
        if (boxRows.size() <= static_cast<int>(index / imagesAcross)) {
            boxRows.push_back(HBox(this));
        }
        boxRows.back().addWidget(images[index].get());
    }
    for (auto& b : boxRows) {
        boxImages.addLayout(b.get());
    }
    updateStatusBar();
    for (auto index : UtilityList::range(urls.size())) {
        auto url = urls[index];
        new FutureBytes(this, url, [this, index] (const auto& ba) { images[index].setBytes(ba); });
    }
}

void SevereDashboard::updateWarnings(PolygonType t) {
    auto label = new ObjectCardBlackHeaderText(this, warningsByType[t].getCount() + " " + warningsByType[t].getName());
    boxWarnings[t].addLayout(label->get());
    for (const auto& w : warningsByType[t].warningList) {
        if (w.isCurrent) {
            auto widget1 = new ObjectCardDashAlertItem(this, w);
            boxWarnings[t].addLayout(widget1->get());
            boxWarnings[t].addWidget(ObjectDividerLine(this).get());
        }
    }
    if (t == PolygonType::ffw) {
        boxWarnings[t].addStretch();
    }
    updateStatusBar();
}

void SevereDashboard::launch(int indexFinal) {
    if (indexFinal == 0) {
        new UsAlerts(this);
    } else if (indexFinal == 1) {
        new SpcStormReports(this, "today");
    } else if (indexFinal > 1) {
        new SpcMcdWatchMpdViewer(this, urls[indexFinal]);
    }
}

void SevereDashboard::updateStatusBar() {
    QString statusTotal = "";
    auto col1 = {PolygonType::mcd, PolygonType::watch, PolygonType::mpd};
    for (const auto& t : col1) {
        statusTotal += "  " + severeNotices[t].getShortName() + ": " + severeNotices[t].getCount();
    }
    for (const auto& t : warningsByType.keys()) {
        statusTotal += "  " + warningsByType[t].getShortName() + ": " + warningsByType[t].getCount();
    }
    setTitle(statusTotal);
}
