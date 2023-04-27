// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef OBJECTNHCSTORMDETAILS_H
#define OBJECTNHCSTORMDETAILS_H

#include <string>
#include <QByteArray>

using std::string;

class NhcStormDetails {
public:
    NhcStormDetails(const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&);
    string getUpdateTime() const;
    string forTopHeader() const;
    string name;
    string movementDir;
    string movementSpeed;
    string pressure;
    string binNumber;
    string stormId;
    string lastUpdate;
    string classification;
    string lat;
    string lon;
    string intensity;
    string status;
    string center;
    string goesUrl;
    string movement;
    string modBinNumber;
    string baseUrl;
    QByteArray coneBytes;
};

#endif  // OBJECTNHCSTORMDETAILS_H
