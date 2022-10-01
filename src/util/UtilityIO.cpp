// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityIO.h"
#include <QFile>
#include <QNetworkAccessManager>
#include <QTextStream>
#include "external/bzlib.h"
#include "objects/File.h"
#include "objects/URL.h"

MemoryBuffer UtilityIO::uncompress(char * compressedData, unsigned int compressedFileSize) {
    unsigned int retSize = 2000000;
    QByteArray outputBuffer(retSize, '0');
    BZ2_bzBuffToBuffDecompress(outputBuffer.data(), &retSize, compressedData, compressedFileSize, 1, 0);
    outputBuffer.resize(retSize);
    return MemoryBuffer{outputBuffer};
}

string UtilityIO::getHtml(const string& url) {
    return URL{url}.getText();
}

QByteArray UtilityIO::downloadAsByteArray(const string& url) {
    return URL{url}.getBytes();
}

string UtilityIO::readTextFile(const string& filePath) {
    return File{filePath}.getText().toStdString();
}

vector<string> UtilityIO::rawFileToStringArray(const string& filePath) {
    // return File{filePath).getText().split(GlobalVariables::newline};
    // TODO FIXME above line seems to cause crash when starting radar - stack size issue?
    vector<string> stringList;
    QFile file;
    file.setFileName(QString::fromStdString(filePath));
    file.open(QIODevice::ReadOnly);
    QTextStream textStream{&file};
    while (true) {
        auto line = textStream.readLine();
        if (line.isNull()) {
            break;
        } else {
            stringList.push_back(line.toStdString());
        }
    }
    if (file.isOpen()) {
        file.close();
    }
    return stringList;
}

QByteArray UtilityIO::readBinaryFileFromResource(const string& srcFile) {
    return File{srcFile}.getBinaryDataFromResource();
}
