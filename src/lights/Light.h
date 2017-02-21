/*
 * Light.h
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#ifndef SRC_LIGHTS_LIGHT_H_
#define SRC_LIGHTS_LIGHT_H_

#include "core/Object3D.h"
#include "math/Color.h"

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

#endif /* SRC_LIGHTS_LIGHT_H_ */
