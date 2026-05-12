/*
 * PointLight.h
 *
 *  Created on: May 12, 2026
 */

#ifndef THREE_LIGHTS_POINTLIGHT_H_
#define THREE_LIGHTS_POINTLIGHT_H_

#include <three/lights/Light.h>

namespace three {

/**
 * PointLight is a light that gets emitted from a single point in all directions.
 * A common use case for this is to replicate the light emitted from a bare lightbulb.
 */
class PointLight: public Light {
public:
  /**
   * Constructs a PointLight.
   * @param color The RGB color of the light.
   * @param intensity The strength/intensity of the light. Default is 1.0.
   * @param distance Maximum range of the light. Default is 0.0 (no limit).
   * @param decay The amount the light dims along the distance of the light. Default is 1.0.
   */
  PointLight(const Color& color, double intensity = 1.0, double distance = 0.0, double decay = 1.0);

  ~PointLight() override;

  double distance;
  double decay;
};

} /* namespace three */

#endif /* THREE_LIGHTS_POINTLIGHT_H_ */