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

/**
 * AmbientLight globally illuminates all objects in the scene equally.
 *
 * This light cannot be used to cast shadows as it does not have a direction.
 */
class AmbientLight: public Light {
public:
  /**
   * Constructs an AmbientLight.
   * @param color The RGB color of the light.
   * @param intensity The strength/intensity of the light. Default is 1.0.
   */
  AmbientLight(const Color& color, double intensity = 1.0);

  ~AmbientLight() override;
};

} /* namespace three */

#endif /* THREE_LIGHTS_AMBIENTLIGHT_H_ */
