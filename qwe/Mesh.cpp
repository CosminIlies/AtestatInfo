#include "Mesh.h"
#include <vector>
#include "Texture.h"




Mesh::Mesh(std::string filePath)
{
	this->vertices = std::vector<Vertex>();
	this->indices = std::vector<unsigned int>();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		Debug::Error("Couldn't load the model from file!");
	}
	else {
		directory = filePath.substr(0, filePath.find_last_of("/"));

		//processMesh(scene->mMeshes[scene->mRootNode->mMeshes[0]], scene);
		processNode(scene->mRootNode, scene);
		std::cout << vertices.size() << " " << indices.size();
		setupMesh();
	}



}

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

	/*glGenVertexArrays(1, &VAO);
	glGenBuffers(NUM_BUFFERS, VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoords));
	*/

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

void Mesh::processNode(aiNode* node, const aiScene* scene)
{


	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene);
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

void Mesh::processMesh(aiMesh* mesh, const aiScene* scene)
{

	for (int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex(
			glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),
			glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y),
			glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		vertices.push_back(vertex);
	}
	for (int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) 
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0) {

	}
}
