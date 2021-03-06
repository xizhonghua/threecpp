/*
 * PerspectiveCamera.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef THREE_CAMERAS_PERSPECTIVECAMERA_H_
#define THREE_CAMERAS_PERSPECTIVECAMERA_H_

#include <three/cameras/Camera.h>

namespace three {

class PerspectiveCamera: public Camera {
public:
  PerspectiveCamera(double fov = 50, double aspect = 1.0, double near = 0.1,
      double far = 2000);
  ~PerspectiveCamera() {
  }

  void updateProjectionMatrix() override;

  double fov { 0.0 };
  double near { 0.1 };
  double far { 2000 };

private:

  // width of the film (default in millimeters)
  double filmGauge { 35 };

  // horizontal film offset (same unit as gauge)
  double filmOffset { 0 };

};

} /* namespace three */

#endif /* THREE_CAMERAS_PERSPECTIVECAMERA_H_ */
