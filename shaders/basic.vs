#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 normalPosition_modelspace;
layout(location = 2) in vec2 vertexUV_modelspace;

// Output data ; will be interpolated for each fragment.
out vec3 Normal;
out vec2 UV;
out vec3 FragPos;

// Values that stay constant for the whole mesh.
uniform mat4 M;
uniform mat4 VP;

void main(){

    mat4 MVP = VP * M;

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
		
	// UV of the vertex. No special space for this one.
	UV = vertexUV_modelspace;
	
	Normal  = normalPosition_modelspace;
	
	FragPos = vec3( M * vec4( vertexPosition_modelspace, 1.0f ) );
	
	
}

//	Normal = mat3( transpose( inverse( model ) ) ) * normalPosition_modelspace;
