/*
 * OpenGLRenderer.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef THREE_RENDERERS_OPENGLRENDERER_H_
#define THREE_RENDERERS_OPENGLRENDERER_H_

#include <vector>

#include <three/renderers/RenderItem.h>

namespace three {

class RenderableObject;

class OpenGLRenderer {
public:
  OpenGLRenderer();
  ~OpenGLRenderer();

  OpenGLRenderer& setSize(int width, int height);
  OpenGLRenderer& setPixelRatio(double pixel_ratio);

  void render(Scene* scene, Camera* camera);

protected:

  void pushRenderItem(RenderableObject* object, Geometry* geometry, Material* material,
      double z);

  void renderObjects(const std::vector<RenderItem>& items, Scene* scene, Camera* camera);
  void projectObject(Object3D* object, Camera* camera);

  void prepareMaterial(Material* material);
  void renderObject(RenderableObject* object);
  void updateProjectionMatrix(Camera* camera);

  int width_ { 0 };
  int height_ { 0 };
  double pixel_ratio_ { 1.0 };

  bool first_ { true };

  // render queues
  int opaqueObjectsLastIndex_ { -1 };
  int transparentObjectsLastIndex_ { -1 };
  std::vector<RenderItem> opaqueObjects_;
  std::vector<RenderItem> transparentObjects_;

};

} /* namespace three */

#endif /* THREE_RENDERERS_OPENGLRENDERER_H_ */
