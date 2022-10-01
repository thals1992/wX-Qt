// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "objects/File.h"
#include <QFile>
#include <QTextStream>
#include <string>

File::File(const string& fileName)
    : fileName{ fileName }
{}

QString File::getText() {
    QFile file;
    file.setFileName(QString::fromStdString(fileName));
    file.open(QIODevice::ReadOnly);
    QTextStream textStream{&file};
    auto stringValue = textStream.readAll();
    if (file.isOpen()) {
        file.close();
    }
    return stringValue;
}

QByteArray File::getBinaryDataFromResource() {
    QFile file{QString::fromStdString(fileName)};
    file.open(QIODevice::ReadOnly);
    auto data = file.readAll();
    if (file.isOpen()) {
        file.close();
    }
    return data;
}
