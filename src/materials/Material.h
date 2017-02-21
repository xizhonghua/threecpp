/*
 * Material.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef MATERIALS_MATERIAL_H_
#define MATERIALS_MATERIAL_H_

#include "math/Color.h"

namespace three {

class Material {
public:
  Material() {
  }

  virtual ~Material() {
  }

  ///////////////////////////////////////////
  // Getter setter
  ///////////////////////////////////////////

  bool wireframe() const {
    return wireframe_;
  }

  Material& wireframe(bool wireframe) {
    this->wireframe_ = wireframe;
    return *this;
  }

  float wireframeLinewidth() const {
    return wireframeLinewidth_;
  }

  Material& wireframeLinewidth(float wireframeLinewidth) {
    this->wireframeLinewidth_ = wireframeLinewidth;
    return *this;
  }

  const Color& color() const {
    return color_;
  }

  Material& color(const Color& color) {
    this->color_ = color;
    return *this;
  }

  bool transparent() const {
    return transparent_;
  }

  Material& transparent(bool transparent) {
    this->transparent_ = transparent;
    return *this;
  }

  bool visiable() const {
    return visiable_;
  }

  Material& visiable(bool visiable) {
    this->visiable_ = visiable;
    return *this;
  }

private:
  Color color_;
  bool wireframe_ { false };
  bool transparent_ { false };
  bool visiable_ { true };
  float wireframeLinewidth_ { 1 };
  bool lights_ { false };
};

} /* namespace three */

#endif /* MATERIALS_MATERIAL_H_ */
