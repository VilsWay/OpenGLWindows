#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include "WindowManager.h"
#include "Triangle.h"
#include "Shader.h"
#include "TextureHandler.h"

using namespace std;

int main()
{
  cout << "Hello There!!" << endl;
 
  //1. Create the Window , make it current context
  WindowManager* wmInst = WindowManager::_getInstance("SampleWindow",800,600);
  glfwMakeContextCurrent(wmInst->_getWindow());
  
  // 2. Intiliaze GLADs
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  glViewport(0, 0, 800, 600);
  // 3. Initializing
  Triangle triangleObj;
  unsigned int tVAO = triangleObj._getSimpleTriangleVAO();
  unsigned int tCVAO = triangleObj._getColorTriangleVAO();
  unsigned int texVAO = triangleObj._getTextureTriangleVAO();
  // 4. Shader Init
  Shader shaderProgram("VertexShaderTexture.txt", "FragmentShaderTexture.txt");

  // Texture Generation
  TextureHandler t;
  unsigned int texture1 = t._getTexture("container.jpg");

  shaderProgram.use();
  shaderProgram.setInt("texture1", 0);

  // 5. Render Loop
  while (!glfwWindowShouldClose(wmInst->_getWindow()))
  {
    //1. Input Processing
    wmInst->ProcessInput();
    
    // 2. Set Frame Color, Reset the color and other buffer
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // 3. Actual Rendering
    shaderProgram.use();
    glBindVertexArray(texVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //4. Frame ready swap the buffer.
    glfwSwapBuffers(wmInst->_getWindow());
    glfwPollEvents();
    
  }
  glfwTerminate();
  return 0;
}
