/*
#  Copyright 2013-present Roman Kushnarenko
#  Licensed under the Apache License, Version 2.0 (the "License")
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#  http:#www.apache.org/licenses/LICENSE-2.0
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#  https:#github.com/sromku/polygon-contains-point
# 
*/

#include "external/ExternalLine.h"

ExternalLine::ExternalLine(ExternalPoint start1, ExternalPoint end1)
    : start{ start1 }
    , end{ end1 }
    , vertical{ false }
    , a{ 999999999.0 }
    , b{ 999999999.0 }
{
    if (end.x - start.x != 0) {
        a = (end.y - start.y) / (end.x - start.x);
        b = start.y - a * start.x;
    } else {
        vertical = true;
    }
}

bool ExternalLine::isVertical() const  {
    return vertical;
}

double ExternalLine::getA() const {
    return a;
}

double ExternalLine::getB() const {
    return b;
}

ExternalPoint ExternalLine::getStart() const {
    return start;
}

bool ExternalLine::isInside(ExternalPoint point) const {
    const auto maxX = start.x > end.x ? start.x : end.x;
    const auto minX = start.x < end.x ? start.x : end.x;
    const auto maxY = start.y > end.y ? start.y : end.y;
    const auto minY = start.y < end.y ? start.y : end.y;
    if ((point.x >= minX && point.x <= maxX) && (point.y >= minY && point.y <= maxY)) {
        return true;
    }
    return false;
}
