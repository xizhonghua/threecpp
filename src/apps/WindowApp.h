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
#include <unordered_map>
#include <iostream>
using namespace std;

namespace three {

class WindowApp {
public:
  WindowApp() {
  }

  WindowApp(int width, int height, std::string title = "ThreeCpp") :
      width_(width), height_(height), title_(title) {
  }

  virtual ~WindowApp() {
  }

  WindowApp& init();
  int run();

  double getPixelRatio() const {
    return pixel_ratio_;
  }

  // Clients need to implement following methods
  virtual void initScene()=0;
  virtual void animate() = 0;

  // Call WindowApp.onKeyXXX() in derived method first for default behavior.
  virtual void onKeyPress(int key, bool shift, bool ctrl, bool alt, bool super);
  virtual void onKeyRelease(int key, bool shift, bool ctrl, bool alt,
      bool super);
  virtual void onKeyRepeat(int key, bool shift, bool ctrl, bool alt,
      bool super);

  static WindowApp* getApp(GLFWwindow* window) {
    return windows_map_[window];
  }

protected:

  std::string title_ { "ThreeCpp" };

  GLFWwindow* window_ { nullptr };
  int width_ { 640 };
  int height_ { 640 };
  double pixel_ratio_ { 1.0 };
private:
  // Map GLFWindows to apps
  static std::unordered_map<GLFWwindow*, WindowApp*> windows_map_;
};

} /* namespace three */

#endif /* SRC_APPS_WINDOWAPP_H_ */
