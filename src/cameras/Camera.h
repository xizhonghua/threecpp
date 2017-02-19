/*
 * Camera.h
 *
 *  Created on: Feb 3, 2017
 *      Author: zxi
 */

#ifndef CAMERAS_CAMERA_H_
#define CAMERAS_CAMERA_H_

#include "core/Object3D.h"
#include "math/Matrix4.h"

namespace three {

class Camera: public Object3D {
public:
  Camera();
  ~Camera();

  Camera& lookAt(const Vector3& target);

  const Matrix4& projectionMatrix() const {
    return projectionMatrix_;
  }

protected:
  Matrix4 projectionMatrix_;
  Matrix4 matrixWorldInverse_;
};

} /* namespace three */

#endif /* CAMERAS_CAMERA_H_ */
