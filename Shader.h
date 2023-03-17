#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>

#include "Debug.h"
#include "DirectionalLight.h"
class Shader
{
public:
	Shader(const std::string& filename);
	~Shader();

	void Bind();

	void loadInteger(const GLchar* location, const int& val);
	void loadFloat(const GLchar* location, const float& val);
	void loadVector(const GLchar* location, const glm::vec3& vector);
	void loadQuaternion(const GLchar* location, const glm::vec4& vector);
	void loadMatrix(const GLchar* location, const glm::mat4& matrix);

	void loadDirectionalLight(DirectionalLight& light);

	//std::string loadShader(const std::string& fileName);
	//void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	//GLuint createShader(const std::string& text, GLenum shaderType);

private:
	static const unsigned int NUM_SHADERS = 2;
	GLuint _program;
	GLuint _shaders[NUM_SHADERS];
	
};

