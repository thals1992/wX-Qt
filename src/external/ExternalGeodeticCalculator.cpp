/* Geodesy by Mike Gavaghan
 *
 * http://www.gavaghan.org/blog/free-source-code/geodesy-library-vincentys-formula/
 *
 * This code may be freely used and modified on any personal or professional
 * project. It comes with no warranty.
 *
 * BitCoin tips graciously accepted at 1FB63FYQMy7hpC2ANVhZ5mSgAZEtY1aVLf
 */

/*
    <p>
    Implementation of Thaddeus Vincenty's algorithms to solve the direct and
    inverse geodetic problems. For more information, see Vincent's original
    publication on the NOAA website:
    </p>
    See http://www.ngs.noaa.gov/PUBS_LIB/inverse.pdf

    @author Mike Gavaghan
 */

#include "external/ExternalGeodeticCalculator.h"
#include <cmath>
#include "external/ExternalAngle.h"

// ExternalGeodeticCalculator::ExternalGeodeticCalculator() {
// }

const double ExternalGeodeticCalculator::twoPi = 2.0 * M_PI;

// Calculate the destination and const double bearing after traveling a specified
// distance, and a specified starting bearing, for an initial location. This
// is the solution to the direct geodetic problem.
//
// @param ellipsoid reference ellipsoid to use
// @param start starting location
// @param startBearing starting bearing (degrees)
// @param distance distance to travel (meters)
// @param endBearing bearing at destination (degrees) element at index 0 will
//                        be populated with the result
// @return
ExternalGlobalCoordinates ExternalGeodeticCalculator::calculateEndingGlobalCoordinates(ExternalGlobalCoordinates start, double startBearing, double distance) {
        QVector<double> dlist = {0.0, 0.0};
        return calculateEndingGlobalCoordinatesOriginal(ExternalEllipsoid::wgs84(), start, startBearing, distance, &dlist);
}

ExternalGlobalCoordinates ExternalGeodeticCalculator::calculateEndingGlobalCoordinatesOriginal(
        ExternalEllipsoid ellipsoid,
        ExternalGlobalCoordinates start,
        double startBearing,
        double distance,
        QVector<double> * endBearing) {
    const double a = ellipsoid.getSemiMajorAxis();
    const double b = ellipsoid.getSemiMinorAxis();
    const double aSquared = a * a;
    const double bSquared = b * b;
    const double f = ellipsoid.getFlattening();
    const double phi1 = ExternalAngle::toRadians(start.getLatitude());
    const double alpha1 = ExternalAngle::toRadians(startBearing);
    const double cosAlpha1 = cos(alpha1);
    const double sinAlpha1 = sin(alpha1);
    const double s = distance;
    const double tanU1 = (1.0 - f) * tan(phi1);
    const double cosU1 = 1.0 / sqrt(1.0 + tanU1 * tanU1);
    const double sinU1 = tanU1 * cosU1;
    // eq. 1
    const double sigma1 = atan2(tanU1, cosAlpha1);
    // eq. 2
    const double sinAlpha = cosU1 * sinAlpha1;
    const double sin2Alpha = sinAlpha * sinAlpha;
    const double cos2Alpha = 1 - sin2Alpha;
    const double uSquared = cos2Alpha * (aSquared - bSquared) / bSquared;
    // eq. 3
    const double A = 1 + (uSquared / 16384) * (4096 + uSquared * (-768 + uSquared * (320 - 175 * uSquared)));
    // eq. 4
    const double B = (uSquared / 1024) * (256 + uSquared * (-128 + uSquared * (74 - 47 * uSquared)));
    // iterate until there is a negligible change in sigma
    const double sOverbA = s / (b * A);
    double sigma = sOverbA;
    double sinSigma;
    double prevSigma = sOverbA;
    double sigmaM2;
    double cosSigmaM2;
    double cos2SigmaM2;
    for (;;) {
        // eq. 5
        sigmaM2 = 2.0 * sigma1 + sigma;
        cosSigmaM2 = cos(sigmaM2);
        cos2SigmaM2 = cosSigmaM2 * cosSigmaM2;
        sinSigma = sin(sigma);
        const double cosSignma = cos(sigma);
        // eq. 6
        double deltaSigma = B * sinSigma * (cosSigmaM2 + (B / 4.0) * (cosSignma * (-1 + 2 * cos2SigmaM2) - (B / 6.0) * cosSigmaM2 * (-3 + 4 * sinSigma * sinSigma) * (-3 + 4 * cos2SigmaM2)));
        // eq. 7
        sigma = sOverbA + deltaSigma;
        // break after converging to tolerance
        if (abs(sigma - prevSigma) < 0.0000000000001) break;

        prevSigma = sigma;
    }
    sigmaM2 = 2.0 * sigma1 + sigma;
    cosSigmaM2 = cos(sigmaM2);
    cos2SigmaM2 = cosSigmaM2 * cosSigmaM2;
    const double cosSigma = cos(sigma);
    sinSigma = sin(sigma);
    // eq. 8
    const double phi2 = atan2(sinU1 * cosSigma + cosU1 * sinSigma * cosAlpha1, (1.0 - f) * sqrt(sin2Alpha + pow(sinU1 * sinSigma - cosU1 * cosSigma * cosAlpha1, 2.0)));
    // eq. 9
    // This fixes the pole crossing defect spotted by Matt Feemster. When a
    // path passes a pole and essentially crosses a line of latitude twice -
    // once in each direction - the longitude calculation got messed up. Using
    // atan2 instead of atan fixes the defect. The change is in the next 3
    // lines.
    // double tanLambda = sinSigma * sinAlpha1 / (cosU1 * cosSigma - sinU1 * sinSigma * cosAlpha1);
    // double lambda = Math.atan(tanLambda);
    const double lambda = atan2(sinSigma * sinAlpha1, (cosU1 * cosSigma - sinU1 * sinSigma * cosAlpha1));
    // eq. 10
    const double C = (f / 16) * cos2Alpha * (4 + f * (4 - 3 * cos2Alpha));
    // eq. 11
    const double L = lambda - (1 - C) * f * sinAlpha * (sigma + C * sinSigma * (cosSigmaM2 + C * cosSigma * (-1 + 2 * cos2SigmaM2)));
    // eq. 12
    const double alpha2 = atan2(sinAlpha, -sinU1 * sinSigma + cosU1 * cosSigma * cosAlpha1);
    // build result
    const double latitude = ExternalAngle::toDegrees(phi2);
    const double longitude = start.getLongitude() + ExternalAngle::toDegrees(L);
    if (endBearing != nullptr && endBearing->size() > 0) {
        (*endBearing)[0] = ExternalAngle::toDegrees(alpha2);
    }
    return ExternalGlobalCoordinates(latitude, longitude);
}
