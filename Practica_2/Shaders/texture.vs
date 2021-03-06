#version 330 core
layout(location=0) in vec3 in_position;
layout(location=1) in vec3 in_color;
layout(location=2) in vec2 in_texCoord;

out vec3 ex_Color;
out vec2 ex_texCoord;

uniform mat4 transform;//Transformación

void main(){
    gl_Position = transform * vec4(in_position, 1);
    // Just pass the color through directly.
    ex_Color = in_color;
    ex_texCoord = vec2(in_texCoord.x, 1.0 - in_texCoord.y);
}