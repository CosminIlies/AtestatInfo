#pragma once
#include "Texture.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"
#include "Window.h"
class Material
{
private:
	Texture* _diffuse;
	Texture* _specular;
	Shader* _shader;
	float _shineDamper;
	float _specularStrength;


public:
	Material(const std::string& shaderFileName, const std::string& textureFileName, const std::string& specularFileName, float shineDamper, float specularStrength);
	Material(const std::string& shaderFileName, const std::string& textureFileName, float shineDamper, float specularStrength);
	~Material();

	void Bind(Transform& transform, Camera& camera, DirectionalLight& light, Window& window);


};

