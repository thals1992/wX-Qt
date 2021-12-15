// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/FutureText.h"
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>
#include <QObject>
#include "util/UtilityDownload.h"

FutureText::FutureText(QWidget * parent, const QString& url, std::function<void(QString)> updateFunc) : QObject(parent) {
    this->updateFunc2 = updateFunc;
    auto watcher = new QFutureWatcher<void>;
    const QFuture<void> future = QtConcurrent::run([this, url] { html = UtilityDownload::getTextProduct(url); });
    watcher->setFuture(future);
    QObject::connect(watcher, &QFutureWatcher<void>::finished, this, [&] { updateFunc2(html); });
}
