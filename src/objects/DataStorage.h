// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <string>

using std::string;

class DataStorage {
public:
    DataStorage();
    explicit DataStorage(const string&);
    void update();
    string getValue() const;
    void setValue(const string&);

private:
    string preference;
    string value;
};

#endif  // DATASTORAGE_H
