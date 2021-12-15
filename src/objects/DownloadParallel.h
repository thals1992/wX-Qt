// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef DOWNLOADPARALLEL_H
#define DOWNLOADPARALLEL_H

#include <QWidget>
#include "objects/FileStorage.h"

class DownloadParallel {
public:
    DownloadParallel(QWidget * parent, FileStorage * fileStorage, QStringList urls);

private:
    void download(int i);
    void update(int i);
    FileStorage * fileStorage;
    QStringList urls;
    QVector<bool> downloadComplete;
};

#endif  // DOWNLOADPARALLEL_H
