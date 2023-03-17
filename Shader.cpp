#include "Shader.h"

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string loadShader(const std::string& fileName);
static GLuint createShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
    int progId = glCreateProgram();
    _program = glCreateProgram();
    _shaders[0] = createShader(loadShader(fileName + ".vert.glsl"), GL_VERTEX_SHADER);
    _shaders[1] = createShader(loadShader(fileName + ".frag.glsl"), GL_FRAGMENT_SHADER);

    for (int i = 0; i < NUM_SHADERS; i++) 
        glAttachShader(_program, _shaders[i]);

    glBindAttribLocation(_program, 0, "position"); 
    glBindAttribLocation(_program, 1, "textureCoords");
    glBindAttribLocation(_program, 2, "normals");
   
    glLinkProgram(_program);
    checkShaderError(_program, GL_LINK_STATUS, true, "Couldn't link the shader program: ");

    glValidateProgram(_program);
    checkShaderError(_program, GL_VALIDATE_STATUS, true, "Program shader is invalid: ");


}

Shader::~Shader()
{

    for (int i = 0; i < NUM_SHADERS; i++) {
        glDetachShader(_program, _shaders[i]);
        glDeleteShader(_shaders[i]);
    }

    glDeleteProgram(_program);
    Debug::Log("Shader was destroyed");
}

void Shader::Bind()
{
    glUseProgram(_program);
}



//uniforms

void Shader::loadInteger(const GLchar* location, const int& val)
{
    unsigned int loc= glGetUniformLocation(_program, location);
    glUniform1i(loc, val);
}

void Shader::loadFloat(const GLchar* location, const float& val)
{
    unsigned int loc = glGetUniformLocation(_program, location);
    glUniform1f(loc, val);

}

void Shader::loadVector(const GLchar* location, const glm::vec3& vector)
{
    unsigned int loc = glGetUniformLocation(_program, location);
    glUniform3f(loc, vector.x, vector.y, vector.z);
}

void Shader::loadQuaternion(const GLchar* location, const glm::vec4& vector)
{
    unsigned int loc = glGetUniformLocation(_program, location);
    glUniform4f(loc, vector.x, vector.y, vector.z, vector.w);
}

void Shader::loadMatrix(const GLchar* location, const glm::mat4& matrix)
{
    unsigned int loc = glGetUniformLocation(_program, location);
    glUniformMatrix4fv(loc,1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::loadDirectionalLight(DirectionalLight& light)
{
    loadVector("light.lightDirection", light.GetDirection());
    loadQuaternion("light.lightColor", light.GetColor());
    loadFloat("light.intensity", light.GetIntensity());
}








static GLuint createShader(const std::string& text, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);

    if (shader == 0) {
        Debug::Error("Couldn't create the shader: ");
    }

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLength[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLength[0] = text.length();

    glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLength);
    glCompileShader(shader);
    checkShaderError(shader, GL_COMPILE_STATUS, false, "Couldn't compile the shader:");

    return shader;
}


static std::string loadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if (file.is_open())
    {
        while (file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else
    {
        Debug::Error("Couldn't load the shader: ");
    }

    return output;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if (success == GL_FALSE)
    {
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        Debug::Error((errorMessage + error).c_str() );
    }
}
