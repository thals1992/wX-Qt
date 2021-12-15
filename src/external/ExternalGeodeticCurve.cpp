/* Geodesy by Mike Gavaghan
 *
 * http://www.gavaghan.org/blog/free-source-code/geodesy-library-vincentys-formula/
 *
 * This code may be freely used and modified on any personal or professional
 * project.  It comes with no warranty.
 *
 * BitCoin tips graciously accepted at 1FB63FYQMy7hpC2ANVhZ5mSgAZEtY1aVLf
 */

// This is the outcome of a geodetic calculation. It represents the path and
// ellipsoidal distance between two GlobalCoordinates for a specified reference
// ellipsoid.
//
// @author Mike Gavaghan

#include "external/ExternalGeodeticCurve.h"

ExternalGeodeticCurve::ExternalGeodeticCurve(double ellipsoidalDistance, double azimuth, double reverseAzimuth) {
    this->ellipsoidalDistance = ellipsoidalDistance;
    this->azimuth = azimuth;
    this->reverseAzimuth = reverseAzimuth;
}
