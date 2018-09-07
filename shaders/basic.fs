#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Normal;
in vec3 FragPos;
in vec3 textureDir; // direction vector representing a 3D texture coordinate

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform vec3 viewPos;

// Tu bi kao trebal slati lightPosition iz main.cpp. Ali za sad mi je ta informacija hardkodirana u ovom shaderu
// uniform vec3 lightPosition;

void main(){

//    vec3 lightPosition = vec3( 10.0f, 4.0f, 0.0f );
	vec3 lightPosition = vec3( 0.0f, 10.0f, 0.0f );
	vec3 objectColor   = vec3( 0.8f,  0.5f, 0.0f );
	// Zadavanje utjecaja svjetla: ambient + diffuse + specular
	vec3 lightColor = vec3( 1.0f, 1.0f, 1.0f );
	
// LIGHT	
	float ambientStrength = 0.4f;
	float specularStrength = 0.9f;
	
	vec3 ambientLight  = ambientStrength * lightColor;
	
	vec3 n_normal   = normalize( Normal );
	vec3 n_lightDir = normalize( lightPosition - FragPos );
	
	float diff = max( dot( n_normal, n_lightDir ), 0.0f );
	vec3 diffuseLight = diff * lightColor;
	
	vec3 viewDir    = normalize( viewPos - FragPos );
	vec3 reflectDir = reflect( -n_lightDir, n_normal );
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
	vec3 specularLight = specularStrength * spec * lightColor;  
	
// TEXTURE	
	vec3 textureColor = texture( myTextureSampler, UV ).rgb;
	
//	color = vec4( ( ambientLight + diffuseLight + specularLight ) * textureColor * objectColor, 1.0f );
	color = vec4( ( ambientLight + diffuseLight + specularLight ) * 1.0f * objectColor, 1.0f );
}
