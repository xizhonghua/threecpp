/*
 * AmbientLight.h
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#ifndef SRC_LIGHTS_AMBIENTLIGHT_H_
#define SRC_LIGHTS_AMBIENTLIGHT_H_

#include <lights/Light.h>

namespace three {

class AmbientLight: public Light {
public:
  AmbientLight(Color color, double intensity=1.0);
  virtual ~AmbientLight();
};

} /* namespace three */

#endif /* SRC_LIGHTS_AMBIENTLIGHT_H_ */
