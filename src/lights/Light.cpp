/*
 * Light.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#include <lights/Light.h>

namespace three {

Light::Light(Color color, double intensity) :
    color(color), intensity(intensity) {
  this->type_ = "Light";
}

Light::~Light() {
}

} /* namespace three */
