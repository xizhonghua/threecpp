/*
 * basic.cc
 *
 *  Created on: Feb 11, 2017
 *      Author: zxi
 */

#include <iostream>
#include <memory>

#include "three.h"
using namespace three;

#include <GLFW/glfw3.h>

int main(void) {
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  const int window_width = 640;
  const int window_height = 640;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(window_width, window_height, "ThreeCPP", NULL,
  NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  std::unique_ptr<Camera> camera(
      new PerspectiveCamera { 75, window_width * 1.0 / window_height, 0, 1e5 });
  camera->position.z = 1000;

  std::unique_ptr<Scene> scene(new Scene);

  std::unique_ptr<Geometry> geometry(new BoxGeometry { 200, 200, 200 });
  std::unique_ptr<Material> material(new MeshBasicMaterial());
  std::unique_ptr<Mesh> mesh(new Mesh(geometry.get(), material.get()));
  scene->add(mesh.get());

  std::unique_ptr<OpenGLRenderer> render(new OpenGLRenderer);
  render->setSize(window_width, window_height);

  glShadeModel(GL_SMOOTH);
//  glEnable(GL_DEPTH_TEST);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glfwSwapInterval(1);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate the mesh
    mesh->rotation.x += 0.5;
    mesh->rotation.y += 1.0;

    // Render the scene from the camera
    render->render(scene.get(), camera.get());

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
