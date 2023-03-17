#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec4 color, float intensity)
{
	this->direction = direction;
	this->color = color;
	this->intensity = intensity;
}

DirectionalLight::~DirectionalLight()
{
}
