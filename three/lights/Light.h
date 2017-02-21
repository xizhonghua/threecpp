/*
 * Light.h
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#ifndef THREE_LIGHTS_LIGHT_H_
#define THREE_LIGHTS_LIGHT_H_

#include <three/core/Object3D.h>
#include <three/math/Color.h>

namespace three {

class Light: public Object3D {
public:
  Light(Color color, double intensity = 1.0);
  virtual ~Light();

  Color color;
  double intensity { 1.0 };
  bool receiveShadow { false };
  bool castShadow { false };

  bool isAmbientLight { false };

};

} /* namespace three */

#endif /* THREE_LIGHTS_LIGHT_H_ */
