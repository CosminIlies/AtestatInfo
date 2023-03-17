#pragma once
#include <glm/glm.hpp>

class Vertex {

public:

	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 textureCoords;

	Vertex(const glm::vec3& pos, const glm::vec2& textureCoords, const glm::vec3& normal) {
		this->pos = pos;
		this->normal = normal;
		this->textureCoords = textureCoords;
	}
	~Vertex() = default;

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec3* GetNormal() { return &normal; }
	inline glm::vec2* GetTextureCoords() { return &textureCoords; }

};