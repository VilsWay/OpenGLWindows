#include "WindowManager.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include "Camera.h"
#include "WindowManager.h"

// set up static variables....
WindowManager* WindowManager::_windowManager = nullptr;
int WindowManager::_width = 0;
int WindowManager::_height = 0;

extern Camera camera;
extern float lastX;
extern float lastY;
extern bool firstMouse;
// timing
extern float deltaTime;	// time between current frame and last frame
extern float lastFrame;

WindowManager::WindowManager(const char* windowName, int width, int height)
{
  _width = width;
  _height = height;
  _initWindow(windowName);
}
void resizeCB(GLFWwindow* window, int width, int height)
{
  glfwSetWindowSize(window, width, height);
  glViewport(0, 0, width, height);
  WindowManager::updateWidthHeight(width, height);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
  if (firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
  camera.ProcessMouseScroll(yoffset);
}


void WindowManager::_initWindow(const char* windowName)
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if (_width <= 0) _width = 400;
  if (_height <= 0) _height = 400;

  _window = glfwCreateWindow(_width, _height, windowName, nullptr, nullptr);

  if (!_window)
  {
    std::cout << "Window Creation failed..." << std::endl;
    glfwTerminate();
    return;
  }
  glfwSetFramebufferSizeCallback(_window, resizeCB);
  //glfwSetCursorPosCallback(_window, mouse_callback);
  glfwSetScrollCallback(_window, scroll_callback);

 
  lastX = _width / 2.0f;
  lastY = _height / 2.0f;
  firstMouse = true;

}


void WindowManager::updateWidthHeight(int width, int height)
{
  _width = width;
  _height = height;
}


GLFWwindow* WindowManager::_getWindow()
{
  return _window;
}

WindowManager* WindowManager::_getInstance(const char* windowName, int width, int height)
{
  if (_windowManager)
  {
    return _windowManager;
  }
  _windowManager = new WindowManager(windowName, width, height);
  return _windowManager;
}

void WindowManager::ProcessInput()
{
  if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(_window, true);

  if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
}




