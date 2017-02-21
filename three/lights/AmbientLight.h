/*
 * AmbientLight.h
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#ifndef THREE_LIGHTS_AMBIENTLIGHT_H_
#define THREE_LIGHTS_AMBIENTLIGHT_H_

#include <three/lights/Light.h>

namespace three {

class AmbientLight: public Light {
public:
  AmbientLight(Color color, double intensity=1.0);
  virtual ~AmbientLight();
};

} /* namespace three */

#endif /* THREE_LIGHTS_AMBIENTLIGHT_H_ */
