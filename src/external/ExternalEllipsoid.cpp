/* Geodesy by Mike Gavaghan
 *
 * http://www.gavaghan.org/blog/free-source-code/geodesy-library-vincentys-formula/
 *
 * This code may be freely used and modified on any personal or professional
 * project.  It comes with no warranty.
 *
 * BitCoin tips graciously accepted at 1FB63FYQMy7hpC2ANVhZ5mSgAZEtY1aVLf
 */

// Encapsulation of an ellipsoid, and declaration of common reference ellipsoids.
// @author Mike Gavaghan

#include "external/ExternalEllipsoid.h"

ExternalEllipsoid::ExternalEllipsoid(double semiMajor, double semiMinor, double flattening, double inverseFlattening) {
    this->semiMajor = semiMajor;
    this->semiMinor = semiMinor;
    this->flattening = flattening;
    this->inverseFlattening = inverseFlattening;
}

double ExternalEllipsoid::getSemiMajorAxis() const {
    return semiMajor;
}

double ExternalEllipsoid::getSemiMinorAxis() const {
    return semiMinor;
}

double ExternalEllipsoid::getFlattening() const {
    return flattening;
}

// double ExternalEllipsoid::getInverseFlattening() const {
//     return inverseFlattening;
// }

ExternalEllipsoid ExternalEllipsoid::wgs84() {
    return fromAAndInverseF(6378137.0, 298.257223563);
}

// Build an Ellipsoid from the semi major axis measurement and the inverse flattening.
ExternalEllipsoid ExternalEllipsoid::fromAAndInverseF(double semiMajor, double inverseFlattening) {
    const double f = 1.0 / inverseFlattening;
    const double b = (1.0 - f) * semiMajor;
    return ExternalEllipsoid(semiMajor, b, f, inverseFlattening);
}

// Build an Ellipsoid from the semi major axis measurement and the flattening.
// ExternalEllipsoid ExternalEllipsoid::fromAAndF(double semiMajor, double flattening) {
//     const double inverseF = 1.0 / flattening;
//     const double b = (1.0 - flattening) * semiMajor;
//     return ExternalEllipsoid(semiMajor, b, flattening, inverseF);
// }
