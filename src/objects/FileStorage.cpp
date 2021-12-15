// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/FileStorage.h"
#include <string>
#include "util/UtilityTime.h"

FileStorage::FileStorage() {
    obsDownloadTimer = DownloadTimer("OBS_AND_WIND_BARBS" + QString::number(UtilityTime::currentTimeMillis()));
}

void FileStorage::clearBuffers() {
    animationMemoryBuffer.clear();
}

void FileStorage::setMemoryBuffer(QByteArray byteArray) {
    memoryBuffer = MemoryBuffer(byteArray);
}

void FileStorage::setMemoryBufferForAnimation(int index, QByteArray byteArray) {
    animationMemoryBuffer[index] = MemoryBuffer(byteArray);
}

void FileStorage::setMemoryBufferForL3TextProducts(const QString& product, QByteArray byteArray) {
    const std::string dataAsStdString(byteArray.constData(), byteArray.length());
    const auto dataAsQString = QString::fromStdString(dataAsStdString);
    level3TextProductMap[product] = dataAsQString;
}
