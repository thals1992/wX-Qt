/*
#
#  Copyright 2013-present Roman Kushnarenko
#  Licensed under the Apache License, Version 2.0 (the 'License')
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#  http://www.apache.org/licenses/LICENSE-2.0
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an 'AS IS' BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#  https://github.com/sromku/polygon-contains-point
#
#
#   The 2D polygon. <br>
#   @see {@link Builder}
#   @author Roman Kushnarenko (sromku@gmail.com)
#*/

#include "external/Builder.h"

Builder::Builder()
        : firstPoint{ true }
        , isClosed{ false }
{}

Builder Builder::addVertex(ExternalPoint point) {
    if (isClosed) {
        // each hole we start with the new array of vertex points
        vertexes.clear();
        isClosed = false;
    }
    updateBoundingBox(point);
    vertexes.push_back(point);
    // add line (edge) to the polygon
    if (vertexes.size() > 1) {
        ExternalLine line{vertexes[vertexes.size() - 2], point};
        sides.push_back(line);
    }
    return *this;
}

void Builder::updateBoundingBox(ExternalPoint point) {
    if (firstPoint) {
        boundingBox =  BoundingBox{};
        boundingBox.xMax = point.x;
        boundingBox.xMin = point.x;
        boundingBox.yMax = point.y;
        boundingBox.yMin = point.y;
        firstPoint = false;
    } else {
        if (point.x > boundingBox.xMax) {
            boundingBox.xMax = point.x;
        } else if (point.x < boundingBox.xMin) {
            boundingBox.xMin = point.x;
        }
        if (point.y > boundingBox.yMax) {
            boundingBox.yMax = point.y;
        } else if (point.y < boundingBox.yMin) {
            boundingBox.yMin = point.y;
        }
    }
}

// Builder * Builder::close() {
//    validate();
//    // add last Line
//    sides.push_back(ExternalLine(vertexes[vertexes.size() - 1], vertexes[0]));
//    isClosed = true;
//    return this;
// }

ExternalPolygon Builder::build() {
    validate();
    // in case you forgot to close
    if (!isClosed) {
        // add last Line
        sides.emplace_back(vertexes[vertexes.size() - 1], vertexes[0]);
    }
    return {sides, boundingBox};
}

void Builder::validate() {
    // if len(self._vertexes) < 3:
    //    print('Polygon must have at least 3 points')
}
