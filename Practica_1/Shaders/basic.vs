#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 ourColor;

uniform mat4 transform;
uniform float offset; //Ej 6

void main()
{
    //gl_Position =  vec4(1.0 * position, 1.0f); // Ej 1, 2 Y 3
    gl_Position = transform * vec4(position, 1.0f); // Ej 4, 7 y 8
	//gl_Position =  vec4(-1.0 * position, 1.0f); // Ej 5
	//gl_Position = vec4( position.x+offset,position.y,position.z, 1.0f); // Ej 6
    ourColor = color;
}