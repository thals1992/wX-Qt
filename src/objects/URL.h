// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef URL_H
#define URL_H

#include <string>
#include <QObject>
#include <QString>

using std::string;

class URL : public QObject{
public:
    explicit URL(const string&);
    string getText();
    string getTextXmlAcceptHeader();
    QByteArray getBytes();

private:
    string url;
};

#endif  // URL_H
