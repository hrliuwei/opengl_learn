#version 330 core
in vec3 ourColor;
in vec2 texCoord;
out vec4 FragColor;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
void main()
{
	FragColor = mix(texture(ourTexture, texCoord), texture(ourTexture2, vec2(texCoord.x + 1.0,texCoord.y + 1.0)), 0.3);
};