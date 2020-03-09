#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include "WindowManager.h"
#include "Triangle.h"
#include "CubeData.h"
#include "Shader.h"
#include "TextureHandler.h"
#include "MatrixOperation.h"
#include "ModelPos.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"



Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 0;
float lastY = 0;
bool firstMouse;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

using namespace std;
int wWidth =1024, wHeight=920;
int main()
{
  cout << "Hello There!!" << endl;
 
  //1. Create the Window , make it current context
  WindowManager* wmInst = WindowManager::_getInstance("SampleWindow", wWidth, wHeight);
  glfwMakeContextCurrent(wmInst->_getWindow());
  
  // 2. Intiliaze GLADs
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  glViewport(0, 0, wWidth, wHeight);
  glEnable(GL_DEPTH_TEST);
  // 3. Initializing
  Triangle triangleObj;
  CubeData cubeDataObj;
  unsigned int tVAO = triangleObj._getSimpleTriangleVAO();
  unsigned int tCVAO = triangleObj._getColorTriangleVAO();
  unsigned int texVAO = triangleObj._getTextureTriangleVAO();
  unsigned int cubeVAO = cubeDataObj._getTexturedCubeVAO();

  // 4. Shader Init
  Shader shaderProgram("VertexShaderTextureMVPCube.txt", "FragmentShaderTextureMVPCube.txt");

  // Texture Generation
  TextureHandler t;
  unsigned int texture1 = t._getTexture("container.jpg");
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);

  projection = glm::perspective(glm::radians(45.f), (float)wWidth / (float)wHeight, 0.1f, 800.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -300.0f));
  
  shaderProgram.use();
  shaderProgram.setInt("texture1", 0);

  shaderProgram.setMat4("projection", projection);
  shaderProgram.setMat4("view", view);
  float angle = 0.5;
  float proj = 0.3f;
  // 5. Render Loop
  while (!glfwWindowShouldClose(wmInst->_getWindow()))
  {
    
    //1. Input Processing
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    wmInst->ProcessInput();
    
    // 2. Set Frame Color, Reset the color and other buffer
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // 3. Actual Rendering
    shaderProgram.use();
    

    for (int i = 0;i < 10; i++)
    {
      model = glm::mat4(1.0f);
      rotate(model, 290.0f + i*10, 0.2, 0.8f, 0.4f);
      translate(model, cubePositions[i]);
      scale(model, 0.5f, 0.5f, 0.5f);
      shaderProgram.setMat4("model", model);

      glBindVertexArray(cubeVAO);
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    view = camera.GetViewMatrix();
    shaderProgram.setMat4("view", view);

    //4. Frame ready swap the buffer.
    glfwSwapBuffers(wmInst->_getWindow());
    glfwPollEvents();
    
  }
  glfwTerminate();
  return 0;
}
