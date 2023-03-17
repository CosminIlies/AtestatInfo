#pragma once
#include<glm/glm.hpp>

class DirectionalLight
{
private:
	glm::vec3 direction;
	glm::vec4 color;
	float intensity;

public:
	DirectionalLight(glm::vec3 direction, glm::vec4 color, float intensity);
	~DirectionalLight();

	inline glm::vec3& GetDirection() { return direction; }
	inline glm::vec4& GetColor() { return color; }
	inline float& GetIntensity() { return intensity; }

};

