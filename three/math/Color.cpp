/*
 * Color.cpp
 *
 *  Created on: Feb 2, 2017
 *      Author: zxi
 */

#include <three/math/Color.h>

namespace three {

Color::Color() {
  this->setRGB(0, 0, 0);
}

Color::Color(float r, float g, float b) {
  this->setRGB(r, g, b);
}

Color::Color(int hex) {
  this->setHex(hex);
}

Color& Color::setRGB(float r, float g, float b) {
  this->r = r;
  this->g = g;
  this->b = b;
  return *this;
}

Color& Color::setHex(int hex) {
  this->r = ((hex >> 16) & 0xff) / 255.0;
  this->g = ((hex >> 8) & 0xff) / 255.0;
  this->b = (hex & 0xff) / 255.0;
  return *this;
}

Color& Color::operator=(int hex) {
  this->setHex(hex);
  return *this;
}

Color::~Color() {

}

} /* namespace three */
