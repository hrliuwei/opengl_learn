#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
uniform Sampler2D screenTexture;

void main()
{
	FragColor = texture(screenTexture, TexCoords).rgb;
    //FragColor = vec4(col, 1.0);
}