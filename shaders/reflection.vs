#version 330 core
layout (location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec3 normalPosition_modelspace;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 M;
uniform mat4 VP;

void main()
{
    gl_Position = VP * M * vec4( vertexPosition_modelspace, 1.0 );
    Normal = mat3( transpose( inverse( M ) ) ) * normalPosition_modelspace;
    FragPos = vec3( M * vec4( vertexPosition_modelspace, 1.0) );
}
