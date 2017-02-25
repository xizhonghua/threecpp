/*
 * GLPrograms.h
 *
 *  Created on: Feb 25, 2017
 *      Author: zxi
 */

#ifndef THREE_RENDERERS_GLPROGRAMS_H_
#define THREE_RENDERERS_GLPROGRAMS_H_

#include <map>
#include <memory>
#include <vector>

#include <three/materials/Material.h>
#include <three/renderers/GLProgram.h>

namespace three {

class GLPrograms {
public:
  GLPrograms();
  ~GLPrograms();

  std::string getProgramCode(Material* material,
      const GLParamtersType& parameters);

  GLProgram* acquireProgram(Material* material,
      const GLParamtersType& parameters, std::string code);

  void releaseProgram(GLProgram* program);

private:
  std::vector<GLProgram*> programs_;

  static std::map<std::string, std::string> ShaderIDs;
};

} /* namespace three */

#endif /* THREE_RENDERERS_GLPROGRAMS_H_ */
