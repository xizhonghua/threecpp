/*
 * WindowApp.cpp
 *
 *  Created on: Feb 19, 2017
 *      Author: zxi
 */

#include <three/apps/WindowApp.h>

#include <cstdlib>

#include <iostream>
#include <functional>

#include <GLFW/glfw3.h>

namespace three {

std::unordered_map<GLFWwindow*, WindowApp*> WindowApp::windows_map_;

void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action,
    int mods) {

  three::WindowApp* app = three::WindowApp::getApp(window);

  if (!app)
    return;

  const bool shift = mods & GLFW_MOD_SHIFT;
  const bool control = mods & GLFW_MOD_CONTROL;
  const bool alt = mods & GLFW_MOD_ALT;
  const bool super = mods & GLFW_MOD_SUPER;

  if (action == GLFW_PRESS) {
    app->onKeyPress(key, shift, control, alt, super);
  } else if (action == GLFW_RELEASE) {
    app->onKeyRelease(key, shift, control, alt, super);
  } else if (action == GLFW_REPEAT) {
    app->onKeyRepeat(key, shift, control, alt, super);
  }
}

void GLFWResizeCallback(GLFWwindow* window, int width, int height) {

  three::WindowApp* app = three::WindowApp::getApp(window);

  if (!app)
    return;

  app->width_ = width;
  app->height_ = height;
  app->aspect_ = width*1.0 / height;

  app->onResize(width, height);
}



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

  windows_map_[window_] = this;

  /* Make the window's context current */
  glfwMakeContextCurrent(window_);

  // bind key callback
  glfwSetKeyCallback(window_, GLFWKeyCallback);
  glfwSetWindowSizeCallback(window_, GLFWResizeCallback);

  glShadeModel(GL_SMOOTH);
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glfwSwapInterval(1);

  GLint m_viewport[4];
  glGetIntegerv( GL_VIEWPORT, m_viewport);

  // Get device pixel ratio
  this->pixel_ratio_ = m_viewport[2] / width_;

  // Call derived class
  this->initScene();

  return *this;
}

void WindowApp::onResize(int width, int height) {
}

void WindowApp::onKeyPress(int key, bool shift, bool ctrl, bool alt,
    bool super) {

  if (key == GLFW_KEY_ESCAPE) {
    glfwSetWindowShouldClose(window_, 1);
  }
}

void WindowApp::onKeyRelease(int key, bool shift, bool ctrl, bool alt,
    bool super) {

}

void WindowApp::onKeyRepeat(int key, bool shift, bool ctrl, bool alt,
    bool super) {

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
