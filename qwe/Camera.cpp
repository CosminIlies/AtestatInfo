#include "Camera.h"
#include <iostream>
Camera::Camera()
{
    position = glm::vec3(0.0, 0.0, 0.0);
    rotation = glm::vec3(0.0, 0.0, 0.0);
}

Camera::Camera(glm::vec3 position, glm::vec3 rotation)
{
    this->position = position;
    this->rotation = rotation;
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetPerspectiveMat(float aspectRatio)
{
    return  glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, 1000.0f);
}

glm::mat4 Camera::GetViewMat() {


    glm::mat4 matrix = glm::mat4(1.0);

    matrix = glm::rotate(matrix, rotation.x, glm::vec3(1.0, 0.0, 0.0));
    matrix = glm::rotate(matrix, rotation.y, glm::vec3(0.0, 1.0, 0.0));
    matrix = glm::rotate(matrix, rotation.z, glm::vec3(0.0, 0.0, 1.0));

    matrix = glm::translate(matrix, -position);



    return matrix;


}