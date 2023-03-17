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

/*glm::mat4 Camera::GetViewMat() {


    glm::mat4 matrix = glm::mat4(1.0);

    glm::vec3 cameraDirection = glm::vec3(
                                    glm::sin(rotation.y) +  glm::cos(rotation.z),
                                    glm::cos(rotation.y) +  glm::sin(rotation.x),
                                    glm::cos(rotation.x) +  glm::sin(rotation.z)
                                );

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);


    matrix = glm::lookAt(position, position +cameraDirection, cameraUp );



    return matrix;
}*/