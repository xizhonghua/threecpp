/*
 * SphereGeometry.h
 *
 *  Created on: May 12, 2026
 *      Author: huahua
 */

#ifndef THREE_GEOMETRIES_SPHEREGEOMETRY_H_
#define THREE_GEOMETRIES_SPHEREGEOMETRY_H_

#include <three/core/Geometry.h>

namespace three {

/**
 * SphereGeometry creates a sphere geometry with the specified parameters.
 * The sphere is constructed by subdividing the surface into a grid of vertices
 * and connecting them with triangular faces.
 */
class SphereGeometry: public Geometry {
public:
  /**
   * Constructs a SphereGeometry.
   * @param radius The radius of the sphere. Default is 1.
   * @param widthSegments The number of horizontal segments. Default is 32.
   * @param heightSegments The number of vertical segments. Default is 16.
   * @param phiStart The starting azimuthal angle in radians. Default is 0.
   * @param phiLength The azimuthal angle length in radians. Default is 2*PI.
   * @param thetaStart The starting polar angle in radians. Default is 0.
   * @param thetaLength The polar angle length in radians. Default is PI.
   */
  SphereGeometry(double radius = 1, int widthSegments = 32, int heightSegments = 16,
      double phiStart = 0, double phiLength = 2 * M_PI, double thetaStart = 0,
      double thetaLength = M_PI);

  ~SphereGeometry();

  // Getters and setters
  double radius() const { return radius_; }
  SphereGeometry& radius(double radius);

  int widthSegments() const { return widthSegments_; }
  SphereGeometry& widthSegments(int widthSegments);

  int heightSegments() const { return heightSegments_; }
  SphereGeometry& heightSegments(int heightSegments);

  double phiStart() const { return phiStart_; }
  SphereGeometry& phiStart(double phiStart);

  double phiLength() const { return phiLength_; }
  SphereGeometry& phiLength(double phiLength);

  double thetaStart() const { return thetaStart_; }
  SphereGeometry& thetaStart(double thetaStart);

  double thetaLength() const { return thetaLength_; }
  SphereGeometry& thetaLength(double thetaLength);

private:
  void generateGeometry();

  double radius_;
  int widthSegments_;
  int heightSegments_;
  double phiStart_;
  double phiLength_;
  double thetaStart_;
  double thetaLength_;
};

} /* namespace three */

#endif /* THREE_GEOMETRIES_SPHEREGEOMETRY_H_ */