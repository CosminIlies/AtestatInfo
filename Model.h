#pragma once
#include <string>
#include <vector>
#include "Mesh.h"
class Model
{
public:
	Model(std::string path) {
		loadModel(path);
		std::cout <<"MESHES: " << meshes.size() << '\n';
	}
	~Model() {
		for (unsigned int i = 0; i < meshes.size(); i++) {
			delete meshes[i];
		}
	};
	void Draw();

private:
	std::vector<Mesh*> meshes;
	

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
};

