/*
 * Geometry.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: zxi
 */

#include <core/Geometry.h>

namespace three {

Geometry::Geometry() {
}

Geometry::~Geometry() {
}

Geometry& Geometry::applyMatrix(const Matrix4& m) {

  for (Vector3& v : vertices) {
    v *= m;
  }

  //TODO(zxi)
  // face normals, etc.

  return *this;
}

} /* namespace three */
