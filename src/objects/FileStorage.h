// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include <QByteArray>
#include <QHash>
#include <QString>
#include <QVector>
#include <memory>
#include "objects/DownloadTimer.h"
#include "objects/MemoryBuffer.h"

class FileStorage {
public:
    FileStorage();
    void clearBuffers();
    void setMemoryBuffer(QByteArray);
    void setMemoryBufferForAnimation(int, QByteArray);
    void setMemoryBufferForL3TextProducts(const QString&, QByteArray);
    QByteArray byteArray;
    MemoryBuffer memoryBuffer;
    QHash<QString, QString> level3TextProductMap;
    QVector<MemoryBuffer> animationMemoryBuffer;
    QString radarInfo = "";
    QString radarDate = "";
    QString radarVcp = "";
    int radarAgeMilli = 0;
    QVector<float> stiData;
    QVector<float> hiData;
    QVector<float> tvsData;
    QStringList obsArr;
    QStringList obsArrExt;
    QStringList obsArrWb;
    QStringList obsArrWbGust;
    QVector<float> obsArrX;
    QVector<float> obsArrY;
    QVector<int> obsArrAviationColor;
    QString obsOldRadarSite;
    DownloadTimer obsDownloadTimer;
};

#endif  // FILESTORAGE_H
