#pragma once
#include<GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>


#include"Debug.h"
#include"Vertex.h"

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();
	void Draw();

private:
	std::string directory;
	enum {
		POSITION_VB,
		TEXTURE_COORDS_VB,
		NORMALS_VB,
		NUM_BUFFERS
	};
	//unsigned int VAO, VBO, EBO;
	unsigned int VAO, VBO[NUM_BUFFERS], EBO;
	void setupMesh();

};