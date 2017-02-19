/*
 * MeshBasicMatrial.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef MATERIALS_MESHBASICMATERIAL_H_
#define MATERIALS_MESHBASICMATERIAL_H_

#include <materials/Material.h>

#include <math/Color.h>

namespace three {

class MeshBasicMaterial: public Material {
public:
  MeshBasicMaterial();
  ~MeshBasicMaterial();

  ///////////////////////////////////////////
  // Getter setter
  ///////////////////////////////////////////

  bool wireframe() const {
    return wireframe_;
  }

  MeshBasicMaterial* wireframe(bool wireframe) {
    this->wireframe_ = wireframe;
    return this;
  }

  float wireframeLinewidth() const {
    return wireframeLinewidth_;
  }

  MeshBasicMaterial* wireframeLinewidth(float wireframeLinewidth) {
    this->wireframeLinewidth_ = wireframeLinewidth;
    return this;
  }

  const Color& color() const {
    return color_;
  }

  MeshBasicMaterial* color(const Color& color) {
    this->color_ = color;
    return this;
  }

protected:
  Color color_;
  bool wireframe_ { false };
  float wireframeLinewidth_ { 1 };
  bool lights_ { false };
};

} /* namespace three */

#endif /* MATERIALS_MESHBASICMATERIAL_H_ */
