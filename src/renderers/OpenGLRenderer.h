/*
 * OpenGLRenderer.h
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#ifndef SRC_RENDERERS_OPENGLRENDERER_H_
#define SRC_RENDERERS_OPENGLRENDERER_H_

#include <vector>

#include "renderers/RenderItem.h"

namespace three {

class OpenGLRenderer {
public:
  OpenGLRenderer();
  ~OpenGLRenderer();

  OpenGLRenderer& setSize(int width, int height);
  OpenGLRenderer& setPixelRatio(double pixel_ratio);

  void render(Scene* scene, Camera* camera);

protected:

  void projectObject(Object3D* object, Camera* camera);
  void pushRenderItem(Object3D* object, Geometry* geometry, Material* material,
      double z);

  void prepareMaterial(Material* material);
  void renderObject(Object3D* object);
  void renderMesh(Mesh* mesh);
  void updateProjectionMatrix(Camera* camera);

  int width_ { 0 };
  int height_ { 0 };
  double pixel_ratio_ { 1.0 };

  bool first_ { true };

  // render queues
  int opaqueObjectsLastIndex { -1 };
  int transparentObjectsLastIndex { -1 };
  std::vector<RenderItem> opaqueObjects_;
  std::vector<RenderItem> transparentObjects;

};

} /* namespace three */

#endif /* SRC_RENDERERS_OPENGLRENDERER_H_ */
