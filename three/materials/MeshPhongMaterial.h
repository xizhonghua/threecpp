#ifndef THREE_MATERIALS_MESHPHONGMATERIAL_H_
#define THREE_MATERIALS_MESHPHONGMATERIAL_H_

#include <three/materials/Material.h>
#include <three/math/Color.h>

namespace three {

class MeshPhongMaterial: public Material {
public:
  MeshPhongMaterial();
  explicit MeshPhongMaterial(const Color& color, const Color& emissive = Color(0x000000),
                             const Color& specular = Color(0x111111), float shininess = 30);
  ~MeshPhongMaterial();

  const Color& emissive() const {
    return emissive_;
  }

  MeshPhongMaterial& emissive(const Color& emissive) {
    this->emissive_ = emissive;
    return *this;
  }

  const Color& specular() const {
    return specular_;
  }

  MeshPhongMaterial& specular(const Color& specular) {
    this->specular_ = specular;
    return *this;
  }

  float shininess() const {
    return shininess_;
  }

  MeshPhongMaterial& shininess(float shininess) {
    this->shininess_ = shininess;
    return *this;
  }

private:
  Color emissive_ { 0x000000 };
  Color specular_ { 0x111111 };
  float shininess_ { 30 };
};

} /* namespace three */

#endif /* THREE_MATERIALS_MESHPHONGMATERIAL_H_ */