#include "Window.h"



Window::Window(int width, int height, const char* title)
{


	_width = width;
	_height = height;
	_title = title;

	if (!glfwInit()) {
		Debug::Error("Couldn't initialize GLFW!");
	}



	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	_window = glfwCreateWindow(_width, _height, _title, 0, 0);

	if (!_window) {
		glfwTerminate();
		Debug::Error("Couldn't create the window!");
	}


	glfwMakeContextCurrent(_window);
	
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetKeyCallback(_window, Input::key_callback);
	glfwSetCursorPosCallback(_window, Input::cursor_position_callback);
	glfwSetMouseButtonCallback(_window, Input::mouse_button_callback);


	
	glViewport(0,0,width, height);

	if (glewInit() != GLEW_OK) {
		Debug::Error("Couldn't initialize GLEW!");
	}
	glEnable(GL_DEPTH_TEST);

}

Window::~Window()
{
	glfwDestroyWindow(_window);
	glfwTerminate();

	Debug::Log("Window was destroyed");
}

bool Window::ShouldCloseTheWindow()
{
	return glfwWindowShouldClose(_window);
}

float Window::GetAspectRatio()
{
	return (float)_width / (float)_height;
}

void Window::ClearScreen() {
	glClearColor(0.0, 0.0, 0.5, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::UpdateWindow()
{

	glfwSwapBuffers(_window);
	glfwPollEvents();
}
