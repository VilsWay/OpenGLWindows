#pragma once
//class GLFWwindow; // forward declaration no use of complete type
#include "GLFW/glfw3.h"
class WindowManager
{

private:
  WindowManager(const char* windowName, int w, int h);
  GLFWwindow* _window = nullptr;
  static int _width, _height;
  void _initWindow(const char* windowName);
  static WindowManager* _windowManager;

public:
  static WindowManager* _getInstance(const char* windowName, int width, int height);
  static void updateWidthHeight(int width, int height);
  GLFWwindow* _getWindow();
  void ProcessInput();
};


