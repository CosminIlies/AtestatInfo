#include "Input.h"


// constructors&deconstructors
Input::Input() {

}

Input::~Input() {
    Debug::Log("Input instance was destroyed!");
}


// getters&setters
bool Input::GetKey(int keyCode) {
    return Input::getInstance()._keys[keyCode];
}
bool Input::GetMouseButton(int keyCode) {
    return Input::getInstance()._mouseButtons[keyCode];
}
glm::vec2 Input::GetMousePosition()
{
    return Input::getInstance()._mousePosition;
}





//singleton

Input& Input::getInstance()
{
    static Input _instance;

    return _instance;
}


//static callbacks

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action != GLFW_RELEASE) {
        Input::getInstance()._keys[key] = true;
    }
    else {
        Input::getInstance()._keys[key] = false;
    }
}

void Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    Input::getInstance()._mousePosition.x = xpos;
    Input::getInstance()._mousePosition.y = ypos;
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action != GLFW_RELEASE) {
        Input::getInstance()._mouseButtons[button] = true;
    } {
        Input::getInstance()._mouseButtons[button] = false;
    }
}
