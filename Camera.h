#pragma once

#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	const float FOV = 60.0f;


public:

	glm::vec3 position;
	glm::vec3 rotation;

	Camera();
	Camera(glm::vec3 position, glm::vec3 rotation);
	~Camera();

	glm::mat4 GetViewMat();
	glm::mat4 GetPerspectiveMat(float aspectRatio);

};

