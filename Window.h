#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Debug.h"
#include "Input.h"

class Window
{
public:

	Window(int width, int height, const char* title);
	~Window();
	bool ShouldCloseTheWindow();
	float GetAspectRatio();
	void ClearScreen();
	void UpdateWindow();


private:
	GLFWwindow* _window;
	int _width, _height;
	const char* _title;
};

