/*
 * OpenGLRenderer.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef THREE_RENDERERS_GLRENDERER_H_
#define THREE_RENDERERS_GLRENDERER_H_

#include <vector>

#include <three/math/Matrix4.h>
#include <three/math/Vector3.h>
#include <three/renderers/RenderItem.h>



namespace three {

class RenderableObject;

class GLRenderer {
public:
  GLRenderer();
  ~GLRenderer();

  GLRenderer& setSize(int width, int height);
  GLRenderer& setPixelRatio(double pixel_ratio);

  void render(Scene* scene, Camera* camera);

protected:

  void pushRenderItem(RenderableObject* object, Geometry* geometry, Material* material,
      double z);

  void renderObjects(const std::vector<RenderItem>& items, Scene* scene, Camera* camera);

  void renderBufferDirect(Camera* camera, void* fog, Geometry* geometry, Material* material, RenderableObject* object, void* group);

  void setMaterial(Material* material);

  void projectObject(Object3D* object, Camera* camera);

  void prepareMaterial(Material* material);
  void renderObject(RenderableObject* object);
  void updateProjectionMatrix(Camera* camera);

  int width_ { 0 };
  int height_ { 0 };
  double pixel_ratio_ { 1.0 };

  bool first_ { true };

  // Camera matrices cache
  Matrix4 projScreenMatrix_;
  Vector3 vector3_;
  Matrix4 matrix4_;
  Matrix4 Matrix42_;

  // Render queues
  int opaqueObjectsLastIndex_ { -1 };
  int transparentObjectsLastIndex_ { -1 };
  std::vector<RenderItem> opaqueObjects_;
  std::vector<RenderItem> transparentObjects_;

};

} /* namespace three */

#endif /* THREE_RENDERERS_GLRENDERER_H_ */
