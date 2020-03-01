#pragma once
#include "glad/glad.h"
#include"GLFW/glfw3.h"
class Triangle
{

private:
  float verticesSimple[9] = {
  -0.5f, -0.5f, 0.0f, // left  
  0.5f, -0.5f, 0.0f, // right 
  0.0f,  0.5f, 0.0f  // top   
  };

  float verticesColor[18] = {
  -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// left  
  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,// right 
  0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top   
  };

  float verticesTexture[24] = {
  -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// left  
  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,// right 
  0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f  // top   
  };

  unsigned int _simpleVAO, _simpleVBO;
  unsigned int _colorVAO, _colorVBO;
  unsigned int _textureVAO, _textureVBO;

  void _GenerateSimpleTriangleVAO()
  {
    // 1. Generate
    glGenVertexArrays(1, &_simpleVAO);
    glGenBuffers(1, &_simpleVBO);
    // 2. Bind 
    glBindVertexArray(_simpleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _simpleVBO);

    // 3. Attach Data
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSimple), verticesSimple, GL_STATIC_DRAW);

    // 4. Set VAO index
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // 5. Enable Vertex Attrib Array.
    glEnableVertexAttribArray(0);

    // 6. Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }


  void _GenerateColorTriangleVAO()
  {
    // 1. Generate
    glGenVertexArrays(1, &_colorVAO);
    glGenBuffers(1, &_colorVBO);
    // 2. Bind 
    glBindVertexArray(_colorVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _colorVBO);

    // 3. Attach Data
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesColor), verticesColor, GL_STATIC_DRAW);

    // 4. Set VAO index
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // 5. Enable Vertex Attrib Array.

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); // 5. Enable Vertex Attrib Array.

    // 6. Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }


  void _GenerateTextureTriangleVAO()
  {
    // 1. Generate
    glGenVertexArrays(1, &_textureVAO);
    glGenBuffers(1, &_textureVBO);
    // 2. Bind 
    glBindVertexArray(_textureVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _textureVBO);

    // 3. Attach Data
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesTexture), verticesTexture, GL_STATIC_DRAW);

    // 4. Set VAO index
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // 5. Enable Vertex Attrib Array.

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1); // 5. Enable Vertex Attrib Array.

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // 6. Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }


public:
  
  //unsigned int getTexturedTriangleVAO(); TODO
  Triangle()
  {
    _GenerateSimpleTriangleVAO();
    _GenerateColorTriangleVAO();
    _GenerateTextureTriangleVAO();
  }

  unsigned int& _getSimpleTriangleVAO()
  {
    return (_simpleVAO);
  }

  unsigned int _getSimpleTriangleVBO()
  {
    return _simpleVBO;
  }

  unsigned int& _getColorTriangleVAO()
  {
    return (_colorVAO);
  }

  unsigned int& _getTextureTriangleVAO()
  {
    return (_textureVAO);
  }

};

