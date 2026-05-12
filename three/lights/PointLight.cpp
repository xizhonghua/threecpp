/*
 * PointLight.cpp
 *
 *  Created on: May 12, 2026
 */

#include <three/lights/PointLight.h>

namespace three {

PointLight::PointLight(const Color& color, double intensity, double distance, double decay) :
    Light(color, intensity), distance(distance), decay(decay) {
  this->type_ = "PointLight";
}

PointLight::~PointLight() {
}

} /* namespace three */