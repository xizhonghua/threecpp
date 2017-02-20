/*
 * WindowApp.cpp
 *
 *  Created on: Feb 19, 2017
 *      Author: zxi
 */

#include <apps/WindowApp.h>
#include <cstdlib>
#include <GLFW/glfw3.h>

namespace three {

WindowApp& WindowApp::init() {

  /* Initialize the library */
  if (!glfwInit())
    exit(-1);

  /* Create a windowed mode window and its OpenGL context */
  window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL,
  NULL);
  if (!window_) {
    glfwTerminate();
    exit(-1);
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window_);

  glShadeModel(GL_SMOOTH);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glfwSwapInterval(1);

  this->initScene();

  return *this;
}

int WindowApp::run() {
  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window_)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->animate();

    /* Swap front and back buffers */
    glfwSwapBuffers(window_);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}

} /* namespace three */
