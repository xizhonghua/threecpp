/*
 * WindowApp.h
 *
 *  Created on: Feb 19, 2017
 *      Author: zxi
 */

#ifndef SRC_APPS_WINDOWAPP_H_
#define SRC_APPS_WINDOWAPP_H_

// forward declaration
class GLFWwindow;

namespace three {

class WindowApp {
public:
  WindowApp() {

  }

  WindowApp(int width, int height) :
      width_(width), height_(height) {

  }

  void init();
  void run();

  // implement following methods
  virtual void initScene()=0;
  virtual void animate() = 0;

  virtual ~WindowApp() {
  }
protected:

  GLFWwindow* window_ { nullptr };
  int width_ { 640 };
  int height_ { 640 };
};

} /* namespace three */

#endif /* SRC_APPS_WINDOWAPP_H_ */
