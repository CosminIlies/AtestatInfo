#include "Transform.h"


Transform::Transform()
{
    this->position = glm::vec3(0.0,0.0, 0.0);
    this->rotation = glm::vec3(0.0, 0.0, 0.0);
    this->scale = glm::vec3(1.0, 1.0, 1.0);
}

Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}

Transform::~Transform()
{
    Debug::Log("Transform was destroyed!");
}

glm::mat4 Transform::getModelMatrix()
{
    glm::mat4 matrix = glm::mat4(1.0);

    matrix = glm::translate(matrix, position);

    matrix = glm::rotate(matrix, rotation.x, glm::vec3(1.0, 0.0, 0.0));
    matrix = glm::rotate(matrix, rotation.y, glm::vec3(0.0, 1.0, 0.0));
    matrix = glm::rotate(matrix, rotation.z, glm::vec3(0.0, 0.0, 1.0));

    matrix = glm::scale(matrix, scale);

    return matrix;
}
