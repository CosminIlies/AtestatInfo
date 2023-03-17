#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normals;

uniform mat4 transformMat;
uniform mat4 perspectiveMat;
uniform mat4 viewMat;

out vec3 f_position;
out vec2 f_textureCoords;
out vec3 f_normals;
out vec3 f_camera_position;



void main(){
	f_position = vec3(transformMat * vec4(position, 1.0));
	f_textureCoords = textureCoords;
	f_normals = (transformMat * vec4(normals, 0.0)).xyz;
	//f_normals = normals;
	//f_normals = mat3(transpose(inverse(transformMat))) * normals;

	f_camera_position = (inverse(viewMat) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - f_position;
	gl_Position =  perspectiveMat * viewMat* transformMat * vec4(position, 1.0);
}