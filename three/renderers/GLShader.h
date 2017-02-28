/*
 * Shader.h
 *
 *  Created on: Feb 27, 2017
 *      Author: zxi
 */

#ifndef THREE_RENDERERS_GLSHADER_H_
#define THREE_RENDERERS_GLSHADER_H_

#include <string>

#include <three/constants.h>

namespace three {

class GLShader {
public:
  GLShader(ShaderType type, const std::string& source);
  ~GLShader() {

  }

  uint32_t id() const {
    return id_;
  }

  ShaderType type() const {
    return type_;
  }


private:
  ShaderType type_;
  std::string source_;
  uint32_t id_;
};

} /* namespace three */

#endif /* THREE_RENDERERS_GLSHADER_H_ */
