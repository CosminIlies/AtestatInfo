#version 330 core

in vec3 f_position;
in vec2 f_textureCoords;
in vec3 f_normals;
in vec3 f_camera_position;

out vec4 out_color;


struct Light{
	vec3 lightDirection;
	vec4 lightColor;
	float intensity;
};

uniform Light light;



struct Material{
	sampler2D diffuse_texture;
	sampler2D specular_texture;
	float shineDamper;
	bool useSpecularTexture;
	float specularStrength;
};

uniform Material material;




vec3 ambientColor = vec3( 0.1, 0.1, 0.1 );


void main(){
	
	vec3 unitNormal = normalize(f_normals);
	vec3 unitLightDirection = normalize(light.lightDirection);
	float brightness = max(dot(-unitLightDirection, unitNormal), 0.0);
	vec4 diffuse = brightness * light.intensity  * light.lightColor;

	

	if(material.shineDamper != 0 || material.specularStrength != 0){
		vec3 viewDir = normalize(f_camera_position - f_position);
		vec3 reflectDir = reflect(unitLightDirection, unitNormal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shineDamper);
		vec4 specular = material.specularStrength * spec * light.lightColor;

		if(material.useSpecularTexture){
			specular *= texture(material.specular_texture, f_textureCoords); 
		}

		out_color = specular + diffuse * texture(material.diffuse_texture, f_textureCoords);
	}else{

		out_color = diffuse * texture(material.diffuse_texture, f_textureCoords);
	}


	
	
}