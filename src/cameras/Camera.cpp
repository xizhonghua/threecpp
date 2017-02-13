/*
 * Camera.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: zxi
 */

#include <cameras/Camera.h>

namespace three {

Camera::Camera() {
}

Camera::~Camera() {
}

Camera& Camera::lookAt(const Vector3& target) {

  Matrix4 m;
  m.lookAt(this->position, target, this->up);

  this->quaternion.setFromRotationMatrix(m);

  return *this;
}

} /* namespace three */
