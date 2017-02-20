/*
 * PerspectiveCamera.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef SRC_CAMERAS_PERSPECTIVECAMERA_H_
#define SRC_CAMERAS_PERSPECTIVECAMERA_H_

#include <cameras/Camera.h>

namespace three {

class PerspectiveCamera: public Camera {
public:
  PerspectiveCamera(double fov = 50, double aspect = 1.0, double near = 0.1,
      double far = 2000);
  ~PerspectiveCamera() {
  }

  void updateProjectionMatrix();

private:

  // width of the film (default in millimeters)
  double filmGauge { 35 };

  // horizontal film offset (same unit as gauge)
  double filmOffset { 0 };

  double fov_ { 0.0 };
  double aspect_ { 1.0 };
  double near_ { 0.1 };
  double far_ { 2000 };
};

} /* namespace three */

#endif /* SRC_CAMERAS_PERSPECTIVECAMERA_H_ */
