/*
 * OpenGLRenderer.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <renderers/OpenGLRenderer.h>

#include <cmath>
#include <iostream>

#include <GLFW/glfw3.h>
#include <GL/glu.h>

#include "three.h"
#include "glExtension.h"

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

  updateProjectionMatrix(camera);

  glMatrixMode(GL_MODELVIEW);

  auto f = [=](Object3D* object) {
    this->renderObject(object);
  };

  scene->traverseVisible(f);
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

//  GLKMatrix4MakeLookAt()
}

void OpenGLRenderer::renderObject(Object3D* object) {

  Mesh* mesh = dynamic_cast<Mesh*>(object);
  if (mesh == nullptr)
    return;

  glPushMatrix();

  glTranslated(mesh->position);

  glRotated(mesh->rotation);

  this->renderMesh(mesh);

  glPopMatrix();
}

void OpenGLRenderer::prepareMaterial(Material* material) {

  glColor3f(material->color().r, material->color().g, material->color().b);

}

void OpenGLRenderer::renderMesh(Mesh* mesh) {

  prepareMaterial(mesh->getMaterial());

  GLenum state;

  if (mesh->getMaterial()->wireframe()) {
    state = GL_LINE_LOOP;
  } else {
    state = GL_TRIANGLES;
  }

  Geometry* const geom = mesh->getGeomtry();

  for (const Face3& f : geom->faces) {
    std::vector<Vector3*> vs = { &(geom->vertices[f.a]), &(geom->vertices[f.b]),
        &(geom->vertices[f.c]) };

    glBegin(state);
    for (Vector3* const v : vs) {
      glVertex3d(v);
    }
    glEnd();
  }

}

} /* namespace three */
