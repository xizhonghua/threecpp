/*
 * RenderItem.h
 *
 *  Created on: Feb 20, 2017
 *      Author: zxi
 */

#ifndef SRC_RENDERERS_RENDERITEM_H_
#define SRC_RENDERERS_RENDERITEM_H_

// Forward declaration
namespace three {
class Camera;
class Geometry;
class Material;
class Mesh;
class Object3D;
class Scene;
} // namespace three

namespace three {
struct RenderItem {
  unsigned long long id;
  Object3D* object;
  Geometry* geometry;
  Material* material;
  double z;
  //TODO(zxi) group
};
}

#endif /* SRC_RENDERERS_RENDERITEM_H_ */
