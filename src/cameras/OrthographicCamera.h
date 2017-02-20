/*
 * OrthographicCamera.h
 *
 *  Created on: Feb 19, 2017
 *      Author: zxi
 */

#ifndef SRC_CAMERAS_ORTHOGRAPHICCAMERA_H_
#define SRC_CAMERAS_ORTHOGRAPHICCAMERA_H_

#include <cameras/Camera.h>

namespace three {

class OrthographicCamera: public Camera {
public:
  OrthographicCamera(double left, double right, double top, double bottom,
      double near = 0.1, double far = 2000);
  ~OrthographicCamera();

  void updateProjectionMatrix() override;

  /////////////////////////////////////////////////////////////////////////////
  // Properties
  // need to call updateProjectionMatrix() after setting
  /////////////////////////////////////////////////////////////////////////////
  double left;
  double right;
  double top;
  double bottom;
  double near;
  double far;
private:

};

} /* namespace three */

#endif /* SRC_CAMERAS_ORTHOGRAPHICCAMERA_H_ */
