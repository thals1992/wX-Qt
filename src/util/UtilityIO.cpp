// *****************************************************************************
// * Copyright (c) 2020, 2021 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityIO.h"
#include <QEventLoop>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTextStream>
#include <memory>
#include <string>
#include "external/bzlib.h"
#include "common/GlobalVariables.h"
#include "util/UtilityLog.h"

MemoryBuffer * UtilityIO::uncompress(char * compressedData, int size) {
    unsigned int retSize = 1000000;
    char * oBuff = new char[retSize];
    const int64_t compressedFileSize = size;
    BZ2_bzBuffToBuffDecompress(oBuff, &retSize, compressedData, compressedFileSize, 1, 0);
    auto dis2 = new MemoryBuffer(oBuff, retSize);
    delete[] oBuff;
    return dis2;
}

QString UtilityIO::getHtml(const QString& url) {
    UtilityLog::d("getHtml " + url);
    QNetworkAccessManager manager;
    auto request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::UserAgentHeader, GlobalVariables::appName + " " + GlobalVariables::appCreatorEmail);
    QNetworkReply * response = manager.get(request);
    QEventLoop event;
    connect(response, &QNetworkReply::finished, &event, &QEventLoop::quit);
    event.exec();
    QString data = response->readAll();
    delete response;
    return data;
}

QByteArray UtilityIO::downloadAsByteArray(const QString& url) {
    UtilityLog::d("getByte " + url);
    QNetworkAccessManager manager;
    QNetworkReply * response = manager.get(QNetworkRequest(QUrl(url)));
    QEventLoop event;
    connect(response, &QNetworkReply::finished, &event, &QEventLoop::quit);
    event.exec();
    const QByteArray byteArray = response->readAll();
    delete response;
    return byteArray;
}

QString UtilityIO::readTextFile(const QString& filePath) {
    auto file = new QFile;
    file->setFileName(filePath);
    file->open(QIODevice::ReadOnly);
    QTextStream textStream(file);
    const QString stringValue = textStream.readAll();
    if (file->isOpen()) {
        file->close();
    }
    delete file;
    return stringValue;
}

QStringList UtilityIO::rawFileToStringArray(const QString& filePath) {
    QStringList stringList;
    auto file = new QFile;
    file->setFileName(filePath);
    file->open(QIODevice::ReadOnly);
    QTextStream textStream(file);
    while (true) {
        QString line = textStream.readLine();
        if (line.isNull()) {
            break;
        } else {
            stringList.push_back(line);
        }
    }
    if (file->isOpen()) {
        file->close();
    }
    delete file;
    return stringList;
}

// QByteArray UtilityIO::getImage(const QString& url) {
//     qDebug() << url;
//     QNetworkAccessManager manager;
//     QNetworkRequest request = QNetworkRequest(QUrl(url));
//     request.setHeader(QNetworkRequest::UserAgentHeader, GlobalVariables::appName + " " + GlobalVariables::appCreatorEmail);
//     QNetworkReply * response = manager.get(request);
//     QEventLoop event;
//     // connect(response, SIGNAL(finished()), &event, SLOT(quit()));
//     connect(response, &QNetworkReply::finished, &event, &QEventLoop::quit);
//     event.exec();
//     QByteArray byteArray = response->readAll();
//     return byteArray;
// }

// MemoryBuffer * UtilityIO::readFileToByteBuffer(QString fileName) {
//     QFile * file = new QFile;
//     file->setFileName(MyApplication::tempDir + fileName);
//     file->open(QIODevice::ReadOnly);
//     std::unique_ptr<QByteArray> data = std::unique_ptr<QByteArray>(new QByteArray());
//     const QByteArray byteArray = file->readAll();
//     // std::unique_ptr<MemoryBuffer> memoryBuffer = std::unique_ptr<MemoryBuffer>(new MemoryBuffer(byteArray));
//     MemoryBuffer * memoryBuffer = new MemoryBuffer(byteArray);
//     if (file->isOpen()) {
//         file->close();
//     }
//     delete file;
//     // return memoryBuffer.get();
//     return memoryBuffer;
// }

// void UtilityIO::saveInputStream(const QString& url, const QString& fileName) {
//     qDebug() << url;
//     QNetworkAccessManager manager;
//     QNetworkReply * response = manager.get(QNetworkRequest(QUrl(url)));
//     QEventLoop event;
//     connect(response, &QNetworkReply::finished, &event, &QEventLoop::quit);
//     event.exec();
//     QString folderName = QString(MyApplication::tempDir);
//     QString saveFilePath = QString(folderName + "/" + fileName);
//     QFile * file = new QFile;
//     file->setFileName(saveFilePath);
//     file->open(QIODevice::WriteOnly);
//     file->write(response->readAll());
//     if (file->isOpen()) {
//         file->close();
//     }
//     delete file;
// }

// QByteArray UtilityIO::saveInputStreamAndReturnBa(QString url, QString fileName) {
//     QNetworkAccessManager manager;
//     QNetworkReply * response = manager.get(QNetworkRequest(QUrl(url)));
//     QEventLoop event;
//     connect(response, &QNetworkReply::finished, &event, &QEventLoop::quit);
//     event.exec();
//     QString folderName = QString(MyApplication::tempDir);
//     QString saveFilePath = QString(folderName + "/" + fileName);
//     QFile * file = new QFile;
//     file->setFileName(saveFilePath);
//     file->open(QIODevice::WriteOnly);
//     const QByteArray byteArray = response->readAll();
//     file->write(byteArray);
//     if (file->isOpen()) {
//         file->close();
//     }
//     delete file;
//     return byteArray;
// }
