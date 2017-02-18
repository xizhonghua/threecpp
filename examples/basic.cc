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
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  PerspectiveCamera camera { 75, 640 / 480.0, 1, 1000 };
  camera.position.z = 1000;

  Scene scene;
  BoxGeometry geometry { 200, 200, 200 };
  MeshBasicMaterial material;
  Mesh mesh(&geometry, &material);
  scene.add(&mesh);
  OpenGLRenderer render;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate the mesh
    mesh.rotation.x += 0.01;
    mesh.rotation.y += 0.02;

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
