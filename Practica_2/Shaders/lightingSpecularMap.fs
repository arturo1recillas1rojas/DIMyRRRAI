#version 330 core


in vec3 FragPos;  
in vec3 Normal;
in vec2 TexCoords;
  
out vec4 color;
uniform sampler2D ourTexture1;

void main()
{

color = texture(ourTexture1, TexCoords);
   
} 