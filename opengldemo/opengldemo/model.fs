#version 330 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{    
    FragColor = texture(texture_diffuse1, texCoords) + texture(texture_specular1, texCoords);
}