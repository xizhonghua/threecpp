/*
 * OpenGLRenderer.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <three/renderers/OpenGLRenderer.h>

#include <cmath>
#include <iostream>

#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include <three/three.h>
#include <three/renderers/glExtension.h>

using namespace std;

namespace three {

OpenGLRenderer::OpenGLRenderer() {
}

OpenGLRenderer::~OpenGLRenderer() {
}

OpenGLRenderer& OpenGLRenderer::setSize(int width, int height) {
  width_ = width;
  height_ = height;

  glViewport(0, 0, width_ * pixel_ratio_, height_ * pixel_ratio_);

  return *this;
}

OpenGLRenderer& OpenGLRenderer::setPixelRatio(double pixel_ratio) {
  this->pixel_ratio_ = pixel_ratio;

  return *this;
}

void OpenGLRenderer::render(Scene* scene, Camera* camera) {

  // update projection
  updateProjectionMatrix(camera);

//TODO(zxi) pre-render

// Reset count
  this->opaqueObjectsLastIndex_ = -1;
  this->transparentObjectsLastIndex_ = -1;

  // Reset object list
  this->opaqueObjects_.clear();
  this->transparentObjects_.clear();

  //TODO(zxi) clipping...

  // Project objects
  projectObject(scene, camera);

  //TODO(zxi) sorting
  //TODO(zxi) setup shadow
  //TODO(zxi) setup lights

  //TODO(zxi) background

  //TOOD(zxi) set blend mode

  // opaque pass (front-to-back order)
  this->renderObjects(opaqueObjects_, scene, camera);

  // transparent pass (back-to-front order)
  this->renderObjects(transparentObjects_, scene, camera);

  // set test bits
//  state.setDepthTest(true);
//  state.setDepthWrite(true);
//  state.setColorWrite(true);

}

void OpenGLRenderer::renderObjects(const std::vector<RenderItem>& items,
    Scene* scene, Camera* camera) {

  for (const RenderItem& item : items) {

    auto object = item.object;
    auto geometry = item.geometry;
    auto material = item.material;

    //TODO(zxi) pass sepaerate parameters
    this->renderObject(object);
  }

}

void OpenGLRenderer::updateProjectionMatrix(Camera* camera) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMultMatrixd(camera->projectionMatrix().elements);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

//TODO(zxi) use camera up
  glMultMatrixd(
      Matrix4::makeLookAt(camera->position, Vector3 { 0, 0, 0 }, Vector3 { 0, 1,
          0 }).elements);
  glRotated(camera->rotation);

  glMatrixMode(GL_MODELVIEW);
}

void OpenGLRenderer::renderObject(RenderableObject* object) {

  glPushMatrix();

  glTranslated(object->position);

  glRotated(object->rotation);

  prepareMaterial(object->getMaterial());

  GLenum state;

  if (object->getMaterial()->wireframe()) {
    state = GL_LINE_LOOP;
  } else {
    state = GL_TRIANGLES;
  }

  Geometry* const geom = object->getGeomtry();

  for (const Face3& f : geom->faces) {
    std::vector<Vector3*> vs = { &(geom->vertices[f.a]), &(geom->vertices[f.b]),
        &(geom->vertices[f.c]) };

    glBegin(state);
    for (Vector3* const v : vs) {
      glVertex3d(v);
    }
    glEnd();
  }

  glPopMatrix();
}

void OpenGLRenderer::prepareMaterial(Material* material) {

  glColor3f(material->color().r, material->color().g, material->color().b);

}

void OpenGLRenderer::projectObject(Object3D* object, Camera* camera) {

  if (!object->visible)
    return;

  //TODO(zxi) check object/camera layer id
  bool visible = true;
  if (!visible)
    goto SKIP;

  if (object->isLight()) {
    //TODO(zxi)
  } else if (object->isMesh() || object->isLine() || object->isPoint()) {

    RenderableObject* renderable = dynamic_cast<RenderableObject*>(object);

    // TODO(zxi) update geometry
    Geometry* geometry = renderable->getGeomtry();
    // TODO(zxi) support material group
    Material* material = renderable->getMaterial();

    // TODO(zxi) compute z
    double z = 0;

    if (material->visiable()) {

      this->pushRenderItem(renderable, geometry, material, z);
    }

  }

  SKIP: for (auto child : object->children) {
    projectObject(child, camera);
  }
}

void OpenGLRenderer::pushRenderItem(RenderableObject* object,
    Geometry* geometry, Material* material, double z) {

  std::vector<RenderItem>* array = nullptr;
  int index = 0;

  if (material->transparent()) {
    array = &transparentObjects_;
    index = ++transparentObjectsLastIndex_;
  } else {
    array = &opaqueObjects_;
    index = ++opaqueObjectsLastIndex_;
  }

  array->push_back({ object->id(), object, geometry, material, z });
}

}
/* namespace three */
