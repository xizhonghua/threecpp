/*
 * SphereGeometry.cpp
 *
 *  Created on: May 12, 2026
 *      Author: huahua
 */

#include <three/geometries/SphereGeometry.h>
#include <cmath>

namespace three {

SphereGeometry::SphereGeometry(double radius, int widthSegments, int heightSegments,
    double phiStart, double phiLength, double thetaStart, double thetaLength) :
    radius_(radius), widthSegments_(widthSegments), heightSegments_(heightSegments),
    phiStart_(phiStart), phiLength_(phiLength), thetaStart_(thetaStart), thetaLength_(thetaLength) {
  generateGeometry();
}

SphereGeometry::~SphereGeometry() {
}

void SphereGeometry::generateGeometry() {
  this->vertices.clear();
  this->faces.clear();

  int vertexCount = (heightSegments_ + 1) * (widthSegments_ + 1);
  this->vertices.reserve(vertexCount);

  for (int i = 0; i <= heightSegments_; ++i) {
    double theta = thetaStart_ + i * thetaLength_ / heightSegments_;
    double sinTheta = std::sin(theta);
    double cosTheta = std::cos(theta);

    for (int j = 0; j <= widthSegments_; ++j) {
      double phi = phiStart_ + j * phiLength_ / widthSegments_;
      double sinPhi = std::sin(phi);
      double cosPhi = std::cos(phi);

      double x = -radius_ * cosPhi * sinTheta;
      double y = radius_ * cosTheta;
      double z = radius_ * sinPhi * sinTheta;

      this->vertices.push_back(Vector3(x, y, z));
    }
  }

  int faceCount = heightSegments_ * widthSegments_ * 2;
  this->faces.reserve(faceCount);

  for (int i = 0; i < heightSegments_; ++i) {
    for (int j = 0; j < widthSegments_; ++j) {
      int a = i * (widthSegments_ + 1) + j;
      int b = (i + 1) * (widthSegments_ + 1) + j;
      int c = (i + 1) * (widthSegments_ + 1) + j + 1;
      int d = i * (widthSegments_ + 1) + j + 1;

      this->faces.push_back(Face3(a, b, d));
      this->faces.push_back(Face3(b, c, d));
    }
  }
}

SphereGeometry& SphereGeometry::radius(double radius) {
  this->radius_ = radius;
  generateGeometry();
  return *this;
}

SphereGeometry& SphereGeometry::widthSegments(int widthSegments) {
  this->widthSegments_ = widthSegments;
  generateGeometry();
  return *this;
}

SphereGeometry& SphereGeometry::heightSegments(int heightSegments) {
  this->heightSegments_ = heightSegments;
  generateGeometry();
  return *this;
}

SphereGeometry& SphereGeometry::phiStart(double phiStart) {
  this->phiStart_ = phiStart;
  generateGeometry();
  return *this;
}

SphereGeometry& SphereGeometry::phiLength(double phiLength) {
  this->phiLength_ = phiLength;
  generateGeometry();
  return *this;
}

SphereGeometry& SphereGeometry::thetaStart(double thetaStart) {
  this->thetaStart_ = thetaStart;
  generateGeometry();
  return *this;
}

SphereGeometry& SphereGeometry::thetaLength(double thetaLength) {
  this->thetaLength_ = thetaLength;
  generateGeometry();
  return *this;
}

} /* namespace three */