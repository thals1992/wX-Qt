// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "misc/SevereDashboard.h"
#include "objects/FutureVoid.h"
#include "objects/FutureBytes.h"
#include "objects/PolygonWatch.h"
#include "spc/SpcMcdWatchMpdViewer.h"
#include "spc/SpcStormReports.h"
#include "misc/UsAlerts.h"
#include "ui/CardBlackHeaderText.h"
#include "ui/CardDashAlertItem.h"
#include "ui/DividerLine.h"
#include "util/DownloadImage.h"
#include "util/To.h"
#include "util/UtilityList.h"

SevereDashboard::SevereDashboard(QWidget * parent)
    : Window{parent}
    , sw{ ScrolledWindow{this, box} }
    , shortcutReload{ Shortcut{QKeySequence{"U"}, this} }
{
    setTitle("Severe Dashboard");
    maximize();

    severeNotices.insert({Watch, SevereNotice{Watch}});
    severeNotices.insert({Mcd, SevereNotice{Mcd}});
    severeNotices.insert({Mpd, SevereNotice{Mpd}});

    warningsByType.insert({Tor, SevereWarning{Tor}});
    warningsByType.insert({Tst, SevereWarning{Tst}});
    warningsByType.insert({Ffw, SevereWarning{Ffw}});

    box.addLayout(boxImages);
    for (auto type : {Tor, Tst, Ffw}) {
        boxWarnings.insert({type, VBox()});
        box.addLayout(boxWarnings.at(type));
    }
    reload();

    shortcutReload.connect([this] { reload(); });
}

void SevereDashboard::reload() {
    for (const auto type : {Tor, Tst, Ffw}) {
        new FutureVoid{this, [this, type] { warningsByType.at(type).download(); }, [this, type] { updateWarnings(type); }};
    }
    new FutureVoid{this, [this] { downloadWatch(); }, [this] { updateWatch(); }};
}

void SevereDashboard::downloadWatch() {
    urls.clear();
    urls.push_back(DownloadImage::byProduct("USWARN"));
    urls.push_back(DownloadImage::byProduct("STRPT"));
    for (const auto& type : {Mcd, Mpd, Watch}) {
        PolygonWatch::byType.at(type)->download();
        severeNotices.at(type).getBitmaps();
        addAll(urls, severeNotices.at(type).urls);
    }
}

void SevereDashboard::updateWatch() {
    for (auto& b : boxRows) {
        b.removeChildren();
    }
    boxImages.removeChildren();
    boxRows.clear();
    images.clear();
    for ([[maybe_unused]] auto index : range(urls.size())) {
        images.emplace_back(this);
        images.back().setNumberAcross(imagesAcross);
    }
    for (auto index : range(urls.size())) {
        shortcuts.emplace_back(QKeySequence{QString::fromStdString(To::string(index + 1))}, this);
        shortcuts.back().connect([this, index] { launch(index); });
        images[index].connect([this, index] { return launch(index); });
        if (boxRows.size() <= static_cast<size_t>(index / imagesAcross)) {
            boxRows.emplace_back();
        }
        boxRows.back().addWidget(images[index]);
    }
    for (auto& b : boxRows) {
        boxImages.addLayout(b);
    }
    updateStatusBar();
    for (auto index : range(urls.size())) {
        new FutureBytes{this, urls[index], [this, index] (const auto& ba) { images[index].setBytes(ba); }};
    }
}

void SevereDashboard::updateWarnings(PolygonType type) {
    if (warningsByType.at(type).getCountAsInt() > 0) {
        boxWarnings[type].removeChildren();
        auto label = std::make_unique<CardBlackHeaderText>(this, warningsByType.at(type).getCount() + " " + warningsByType.at(type).getName());
        boxWarnings[type].addLayout(label->getView());
        for (const auto& warning : warningsByType.at(type).warningList) {
            if (warning.isCurrent) {
                auto widget1 = std::make_unique<CardDashAlertItem>(this, warning);
                boxWarnings[type].addLayout(widget1->getView());
                boxWarnings[type].addWidget(DividerLine{this}.get());
            }
        }
//        if (type == Ffw) {
            boxWarnings[type].addStretch();
//        }
        updateStatusBar();
    }
}

void SevereDashboard::launch(int indexFinal) {
    if (indexFinal == 0) {
        new UsAlerts{this};
    } else if (indexFinal == 1) {
        new SpcStormReports{this, "today"};
    } else if (indexFinal > 1) {
        new SpcMcdWatchMpdViewer{this, urls[indexFinal]};
    }
}

void SevereDashboard::updateStatusBar() {
    string statusTotal;
    for (const auto& type : {Mcd, Watch, Mpd}) {
        if (severeNotices.at(type).getCountAsInt() > 0) {
            statusTotal += "  " + severeNotices.at(type).getShortName() + ": " + severeNotices.at(type).getCount();
        }
    }
    for (const auto& type : warningsByType) {
        if (type.second.getCountAsInt() > 0) {
            statusTotal += "  " + type.second.getShortName() + ": " + type.second.getCount();
        }
    }
    setTitle(statusTotal);
}
