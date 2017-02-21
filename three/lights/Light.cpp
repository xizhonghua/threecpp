/*
 * Light.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#include <three/lights/Light.h>

namespace three {

Light::Light(Color color, double intensity) :
    color(color), intensity(intensity) {
  this->type_ = "Light";
  this->isLight_ = true;
}

Light::~Light() {
}

} /* namespace three */
