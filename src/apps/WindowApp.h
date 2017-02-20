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

#include <string>

namespace three {

class WindowApp {
public:
  WindowApp() {

  }

  WindowApp(int width, int height, std::string title = "ThreeCpp") :
      width_(width), height_(height), title_(title) {

  }

  WindowApp& init();
  int run();

  // implement following methods
  virtual void initScene()=0;
  virtual void animate() = 0;

  virtual ~WindowApp() {
  }
protected:

  std::string title_ { "ThreeCpp" };

  GLFWwindow* window_ { nullptr };
  int width_ { 640 };
  int height_ { 640 };
};

} /* namespace three */

#endif /* SRC_APPS_WINDOWAPP_H_ */
