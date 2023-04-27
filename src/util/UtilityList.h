// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#ifndef UTILITYLIST_H
#define UTILITYLIST_H

#include <functional>
#include <string>
#include <vector>
#include <QStringList>

using std::function;
using std::string;
using std::vector;

vector<int> range(size_t);
vector<int> range2(int, size_t);
vector<int> range3(int, size_t, int);

template<typename T> vector<std::pair<int, T>> enumerate(vector<T> vec) {
    vector<std::pair<int, T>> enumeratedList;
    auto i = 0;
    for (const auto& item : vec) {
        enumeratedList.push_back(std::make_pair(i,item));
        i += 1;
    }
    return enumeratedList;
}

// void for_each_index(const vector<string>&, const function<void(int, string)>&);

template<typename T> static bool contains(const vector<T>& items, const T& v) {
    if (find(items.begin(), items.end(), v) != items.end()) {
        return true;
    } else {
        return false;
    }
}

int findex(const string&, const vector<string>&);
int findex(const string&, const QStringList&);
int indexOf(const vector<string>&, const string&);
template<typename T> static void addAll(T& a, const T& b) { a.insert(a.end(), b.begin(), b.end()); }

class UtilityList {
public:
    static int count(const vector<string>&, const string&);
    static vector<string> reversed(const vector<string>&);
    template<typename T> static void addAll(T& a, const T& b) { a.extend(b); }
};

#endif  // UTILITYLIST_H
