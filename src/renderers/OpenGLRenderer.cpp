/*
 * OpenGLRenderer.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: zxi
 */

#include <renderers/OpenGLRenderer.h>

#include <iostream>

#include <GLFW/glfw3.h>

#include <cameras/Camera.h>
#include <scenes/Scene.h>



namespace three {

OpenGLRenderer::OpenGLRenderer() {
  // TODO Auto-generated constructor stub

}

OpenGLRenderer::~OpenGLRenderer() {
  // TODO Auto-generated destructor stub
}

void OpenGLRenderer::render(Scene* scene, Camera* camera) {
  //TODO(zxi)
  std::cerr << "rendering..." << std::endl;

  glBegin(GL_LINE);
  glColor3f(1, 1, 1);
  glVertex2d(10, 10);
  glVertex2d(100, 100);
  glEnd();
}

} /* namespace three */
