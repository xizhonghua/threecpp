/*
 * AmbientLight.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#include <three/lights/AmbientLight.h>

namespace three {

AmbientLight::AmbientLight(Color color, double intensity) :
    Light(color, intensity) {
  this->type_ = "AmbientLight";
  this->castShadow = false;
}

AmbientLight::~AmbientLight() {
}

} /* namespace three */
