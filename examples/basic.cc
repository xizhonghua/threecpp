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

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  PerspectiveCamera camera { 75, 640.0 / 640.0, 1, 1000 };
  camera.position.z = 3;
  std::cerr << "Camera position " << camera.position << std::endl;

  Scene scene;
  std::unique_ptr<Geometry> geometry(new BoxGeometry { 1, 1, 1 });
  std::unique_ptr<Material> material(new MeshBasicMaterial());
  std::unique_ptr<Mesh> mesh(new Mesh(geometry.get(), material.get()));
  scene.add(mesh.get());
  OpenGLRenderer render;

  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glClearColor(1.0, 1.0, 1.0, 1.0);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate the mesh
    mesh->rotation.x += 0.1;
    mesh->rotation.y += 0.2;

    // Render the scene from the camera
    render.render(&scene, &camera);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
