/*
 * Shader.h
 *
 *  Created on: Feb 27, 2017
 *      Author: zxi
 */

#ifndef THREE_RENDERERS_SHADER_H_
#define THREE_RENDERERS_SHADER_H_

#include <string>

#include <three/renderers/GLUniforms.h>

namespace three {

// A wrapper of uniforms, vertexGLSL and fragmentGLSL
class Shader {
public:
  Shader(const GLUniforms& uniforms, const std::string& vertexGLSL,
      const std::string& fragmentGLSL) :
      uniforms(uniforms), vertexGLSL(vertexGLSL), fragmentGLSL(fragmentGLSL) {
  }
  ~Shader() {
  }

  GLUniforms uniforms;
  std::string vertexGLSL;
  std::string fragmentGLSL;
};

} /* namespace three */

#endif /* THREE_RENDERERS_SHADER_H_ */
