#include "Mesh.h"
#include <vector>
#include "Texture.h"


Mesh::Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> indices) {
	this->vertices = vertices;
	this->indices = indices;

	setupMesh();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	Debug::Log("Mesh was destroyed");
}

void Mesh::Draw() {

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Mesh::setupMesh() {


	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textureCoords;
	std::vector<glm::vec3> normals;

	int numVertices =  vertices.size();

	positions.reserve(vertices.size());
	textureCoords.reserve(vertices.size());
	normals.reserve(vertices.size());

	for (int i = 0; i < vertices.size(); i++) {
		positions.push_back(*vertices[i].GetPos());
		textureCoords.push_back(*vertices[i].GetTextureCoords());
		normals.push_back(*vertices[i].GetNormal());
	}
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glGenBuffers(NUM_BUFFERS, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE_COORDS_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(textureCoords[0]), &textureCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMALS_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);




	glBindVertexArray(0);
}