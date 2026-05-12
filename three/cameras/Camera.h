/*
 * Camera.h
 *
 *  Created on: Feb 3, 2017
 *      Author: zxi
 */

#ifndef THREE_CAMERAS_CAMERA_H_
#define THREE_CAMERAS_CAMERA_H_

#include <three/core/Object3D.h>
#include <three/math/Matrix4.h>

namespace three {

class Camera: public Object3D {
public:
  Camera();
  virtual ~Camera();

  Camera& lookAt(const Vector3& target);

  const Matrix4& projectionMatrix() const {
    return projectionMatrix_;
  }

  // Update the camera's projection matrix when the window is resized.
  virtual void onResize(int width, int height);
  
  // Update the camera's projection matrix. Should be called after changing properties like aspect, zoom, etc.
  virtual void updateProjectionMatrix() = 0;

  // public properties
  double zoom { 1.0 };
  double aspect { 1.0 };

  Matrix4 matrixWorldInverse;

protected:
  Matrix4 projectionMatrix_;


};

} /* namespace three */

#endif /* THREE_CAMERAS_CAMERA_H_ */
