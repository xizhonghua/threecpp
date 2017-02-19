/*
 * Color.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#include <math/Color.h>

namespace three {

Color::Color(float r, float g, float b) {
  this->setRGB(r, g, b);
}

Color::Color(int hex) {
  r = ((hex >> 16) & 0xff) / 255.0;
  g = ((hex >> 8) & 0xff) / 255.0;
  b = (hex & 0xff) / 255.0;
}

Color& Color::setRGB(float r, float g, float b) {
  this->r = r;
  this->g = g;
  this->b = b;
  return *this;
}

Color::~Color() {
  // TODO Auto-generated destructor stub
}

} /* namespace three */
