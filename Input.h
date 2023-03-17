#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Debug.h"

class Input
{



public:
	Input();
	~Input();

	static Input& getInstance();
	bool _keys[256] = { false };
	bool _mouseButtons[16] = { false };
	glm::vec2 _mousePosition = glm::vec2(0, 0);


	bool GetKey(int keyCode);
	bool GetMouseButton(int keyCode);
	glm::vec2 GetMousePosition();

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};



