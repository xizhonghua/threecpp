/*
 * GLProgram.h
 *
 *  Created on: Feb 25, 2017
 *      Author: zxi
 */

#ifndef THREE_RENDERERS_GLPROGRAM_H_
#define THREE_RENDERERS_GLPROGRAM_H_

#include <cstdint>
#include <map>
#include <string>

#include <three/materials/Material.h>

namespace three {

typedef std::map<std::string, std::string> GLParamtersType;

class GLProgram {
public:
  explicit GLProgram(const std::string& code, Material* material, const GLParamtersType& parameters);

  // Does not allow copy and assign
  GLProgram(const GLProgram&) = delete;
  GLProgram& operator=(const GLProgram&) = delete;

  GLProgram(GLProgram&&) = default;

  ~GLProgram();

  uint32_t id() const {
    return id_;
  }

  std::string code() const {
    return code_;
  }

  uint32_t usedTimes { 1 };

private:
  static uint32_t programIdCount;

  uint32_t id_;
  std::string code_;
  uint32_t program_;

};

} /* namespace three */

#endif /* THREE_RENDERERS_GLPROGRAM_H_ */
