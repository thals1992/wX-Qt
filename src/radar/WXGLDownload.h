// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef WXGLDOWNLOAD_H
#define WXGLDOWNLOAD_H

#include <QStringList>
#include <QWidget>
#include "objects/FileStorage.h"

class WXGLDownload {
public:
    static void getNidsTab(const QString&, const QString&, FileStorage&);
    static QString getRidPrefix(const QString&, bool);
    static QString getRadarDirectoryUrl(const QString&, const QString&, const QString&);
    static QString getRadarFileUrl(const QString&, const QString&, bool);
    static void getRadarFile(const QString&, const QString&, const QString&, const QString&);
    static void getRadarFilesForAnimation(QWidget *, int, const QString&, const QString&, FileStorage *);

private:
    static const QString pattern1;
    static const QString pattern2;
    static const QString nwsRadarPub;
    static const QStringList pacRids;
};

#endif  // WXGLDOWNLOAD_H
