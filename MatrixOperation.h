#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

void rotate(glm::mat4& mat, float angle, float x, float y, float z)
{
  mat = glm::rotate(mat, glm::radians(angle), glm::vec3(x,y,z));
}

void scale(glm::mat4& mat, float x, float y, float z)
{
  mat = glm::scale(mat, glm::vec3(x, y, z));
}

void translate(glm::mat4& mat, float x, float y, float z)
{
  mat = glm::translate(mat, glm::vec3(x, y, z));
}

void translate(glm::mat4& mat, glm::vec3 v1)
{
  mat = glm::translate(mat, v1);
}


