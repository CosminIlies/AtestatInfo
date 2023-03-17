#include "Material.h"
#include "Window.h"

Material::Material(const std::string& shaderFileName, const std::string& textureFileName, const std::string& specularFileName, float shineDamper, float specularStrength)
{
	_shader = new Shader(shaderFileName);
	_diffuse = new Texture(textureFileName);
	_specular = new Texture(specularFileName);
	_shineDamper = shineDamper;
	_specularStrength = specularStrength;
}

Material::Material(const std::string& shaderFileName, const std::string& textureFileName, float shineDamper, float specularStrength)
{
	_shader = new Shader(shaderFileName);
	_diffuse = new Texture(textureFileName);
	_shineDamper = shineDamper;
	_specularStrength = specularStrength;
}

Material::~Material()
{
	delete _shader;
	delete _diffuse;
	if (_specular != nullptr)
		delete _specular;
}

void Material::Bind(Transform& transform, Camera& camera, DirectionalLight& light, Window& window)
{
	_shader->Bind();
	_diffuse->Bind(0);
	if (_specular != nullptr) {
		_specular->Bind(1);
		_shader->loadInteger("material.useSpecularTexture", 1);
	}
	_shader->loadDirectionalLight(light);
	_shader->loadInteger("material.specular_texture", 1);
	_shader->loadMatrix("viewMat", camera.GetViewMat());
	_shader->loadMatrix("perspectiveMat", camera.GetPerspectiveMat(window.GetAspectRatio()));
	_shader->loadMatrix("transformMat", transform.getModelMatrix());

	_shader->loadFloat("material.shineDamper", _shineDamper);
	_shader->loadFloat("material.specularStrength", _specularStrength);
}

