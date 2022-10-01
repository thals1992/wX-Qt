// *****************************************************************************
// * Copyright (c) 2020, 2021, 2022 joshua.tee@gmail.com. All rights reserved.
// *
// * Refer to the COPYING file of the official project for license.
// *****************************************************************************

#include "util/UtilityList.h"
#include "objects/WString.h"

// void for_each_index(const vector<string>& vec, const function<void(int, string)>& fn) {
//     auto i = 0;
//     for (const auto& v : vec) {
//         fn(i, v);
//         i += 1;
//     }
// }

// template<typename T> void for_each_index(vector<T>& vec, function<void(int, int)> fn) {
//    auto i = 0;
//    for (auto v : vec) {
//        fn(i, v);
//        i += 1;
//    }
// }

int findex(const string& value, const vector<string>& items) {
    for (auto index : range(items.size())) {
        if (WString::startsWith(items[index], value)) {
            return index;
        }
    }
    return 0;
}

int findex(const string& value, const QStringList& items) {
    for (auto index : range(items.size())) {
        if (WString::startsWith(items[index].toStdString(), value)) {
            return index;
        }
    }
    return 0;
}

int indexOf(const vector<string>& items, const string& value) {
//    for (size_t index = 0; index < items.size(); index++) {
//        if (items[index] == value) {
//            return index;
//        }
//    }
//    return 0;

    auto ret = std::find(items.begin(), items.end(), value);
    if (ret != items.end()) {
        return ret - items.begin();
    }
    return 0;
}

vector<int> range(size_t count) {
    vector<int> list;
    for (size_t index = 0; index < count; index++) {
        list.push_back(static_cast<int>(index));
    }
    return list;
}

vector<int> range2(int from, size_t to) {
    vector<int> list;
    for (size_t i = from; i < to; i += 1) {
        list.push_back(static_cast<int>(i));
    }
    return list;
}

vector<int> range3(int from, size_t to, int by) {
    vector<int> list;
    for (size_t i = from; i < to; i += by) {
        list.push_back(static_cast<int>(i));
    }
    return list;
}

int UtilityList::count(const vector<string>& items, const string& s) {
    // auto count = 0;
    // for (const string& item : al) {
    //     if (item == data) {
    //         count += 1;
    //     }
    // }
    // return count;
    return std::count(std::begin(items), std::end(items), s);
}

vector<string> UtilityList::reversed(const vector<string>& items) {
    vector<string> returnList = items;
    std::reverse(returnList.begin(), returnList.end());
    return items;
}
