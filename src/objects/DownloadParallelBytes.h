// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef DOWNLOADPARALLELBYTES_H
#define DOWNLOADPARALLELBYTES_H

#include <QWidget>

class DownloadParallelBytes {
public:
    DownloadParallelBytes(QWidget *, QStringList);
    QVector<QByteArray> byteList;

private:
    void download(int i);
    void update(int i);    
    QStringList urls;
    QVector<bool> downloadComplete;
};

#endif  // DOWNLOADPARALLELBYTES_H
