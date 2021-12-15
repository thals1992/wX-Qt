/* Geodesy by Mike Gavaghan
 *
 * http://www.gavaghan.org/blog/free-source-code/geodesy-library-vincentys-formula/
 *
 * This code may be freely used and modified on any personal or professional
 * project.  It comes with no warranty.
 *
 * BitCoin tips graciously accepted at 1FB63FYQMy7hpC2ANVhZ5mSgAZEtY1aVLf
 */

#include "external/ExternalGeodeticMeasurement.h"
#include <cmath>

ExternalGeodeticMeasurement::ExternalGeodeticMeasurement(
        double ellipsoidalDistance,
        double azimuth,
        double reverseAzimuth,
        double elevationChange
) : ExternalGeodeticCurve(ellipsoidalDistance, azimuth, reverseAzimuth) {
    this->elevationChange = elevationChange;
    p2p = sqrt(ellipsoidalDistance * ellipsoidalDistance + elevationChange * elevationChange);
}

// double ExternalGeodeticMeasurement::getElevationChange() const {
//     return elevationChange;
// }

// double ExternalGeodeticMeasurement::getPointToPointDistance() const {
//     return p2p;
// }
