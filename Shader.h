#ifndef  SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/glm.hpp"

class Shader {
public:
  unsigned int ID;
  Shader(const char* vertexPath, const char* fragmentPath);
  void use();
  void setFloat(const std::string& name, float value);
  void setInt(const std::string& name, int value);
  void setMat4(const std::string& name, const glm::mat4& mat) const;
private:
  void CheckCompileStatus(unsigned int shader, std::string type);
  
};

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

  std::string vertexSource;
  std::string fragmentSource;

  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  try
  {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);

    std::stringstream vertexStream, fragmentStream;
    vertexStream << vShaderFile.rdbuf();
    fragmentStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexSource = vertexStream.str();
    fragmentSource = fragmentStream.str();

  }
  catch (std::ifstream::failure e)
  {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }

  const char* vShaderCode = vertexSource.c_str();
  const char* fShaderCode = fragmentSource.c_str();

  unsigned int vShader, fShader;
  vShader = glCreateShader(GL_VERTEX_SHADER);
  fShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vShader, 1, &vShaderCode, NULL);
  glShaderSource(fShader, 1, &fShaderCode, NULL);

  glCompileShader(vShader);
  CheckCompileStatus(vShader, "shader");

  glCompileShader(fShader);
  CheckCompileStatus(fShader, "shader");



  ID = glCreateProgram();
  glAttachShader(ID, vShader);
  glAttachShader(ID, fShader);
  glLinkProgram(ID);

  CheckCompileStatus(ID, "program");

  glDeleteShader(vShader);
  glDeleteShader(fShader);
}

void Shader::use()
{
  glUseProgram(ID);
}

void Shader::CheckCompileStatus(unsigned int shader, std::string type)
{
  int success;
  char infolog[512];
  if (type != "program")
  {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(shader, 512, NULL, infolog);
      std::cout << "Error in compiling Shader ..." << infolog << std::endl;
    }
  }
  else
  {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(shader, 512, NULL, infolog);
      std::cout << "Error in linking program.." << std::endl;
    }
  }
}


void Shader::setFloat(const std::string& name, float value)
{
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, int value)
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

#endif // ! _SHADER




