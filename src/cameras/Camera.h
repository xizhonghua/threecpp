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
  virtual ~Camera();

  Camera& lookAt(const Vector3& target);

  const Matrix4& projectionMatrix() const {
    return projectionMatrix_;
  }

  virtual void updateProjectionMatrix() = 0;

  // public properties
  double zoom { 1.0 };
  double aspect { 1.0 };

protected:
  Matrix4 projectionMatrix_;
  Matrix4 matrixWorldInverse_;

};

} /* namespace three */

#endif /* CAMERAS_CAMERA_H_ */
