#version 330 core
//out vec4 color;
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform samplerCube skybox;

void main()
{

/// 	vec3 lightPosition = vec3( 0.0f, 10.0f, 0.0f );
/// 	vec3 objectColor   = vec3( 0.8f,  0.5f, 0.0f );
/// 	// Zadavanje utjecaja svjetla: ambient + diffuse + specular
/// 	vec3 lightColor = vec3( 1.0f, 1.0f, 1.0f );
	
// LIGHT	
/// 	float ambientStrength = 0.4f;
/// 	float specularStrength = 0.9f;
/// 	
/// 	vec3 ambientLight  = ambientStrength * lightColor;
/// 	
/// 	vec3 n_normal   = normalize( Normal );
/// 	vec3 n_lightDir = normalize( lightPosition - FragPos );
/// 	
/// 	float diff = max( dot( n_normal, n_lightDir ), 0.0f );
/// 	vec3 diffuseLight = diff * lightColor;
/// 	
/// 	vec3 viewDir    = normalize( viewPos - FragPos );
/// 	vec3 reflectDir = reflect( -n_lightDir, n_normal );
/// 
/// 	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
/// 	vec3 specularLight = specularStrength * spec * lightColor;  

// TEXTURE	
    // OVO JE ZA REFLECTION
    vec3 I = normalize( FragPos - viewPos );
    vec3 R = reflect( I, normalize( Normal ) );
    FragColor = vec4( texture( skybox, R ).rgb, 1.0 ) * vec4( 0.7f, 0.3f, 0.5f, 1.0f);

    // OVO JE ZA REFRACTION
///     float ratio = 1.00 / 1.52;
///     vec3 I = normalize( FragPos - viewPos );
///     vec3 R = refract( I, normalize( Normal ), ratio );
///     FragColor = vec4( texture( skybox, R ).rgb, 1.0 );
    
//	color = vec4( ( ambientLight + diffuseLight + specularLight ) * textureColor * objectColor, 1.0f );
//  ovaj donji je pravi!
//	color = vec4( ( ambientLight + diffuseLight + specularLight ) * 1.0f * objectColor, 1.0f );
}
