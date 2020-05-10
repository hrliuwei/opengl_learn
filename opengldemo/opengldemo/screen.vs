#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	TexCoords = aTexCoords;
    gl_Position = (aPos.x, aPos.y, 0.0, 1.0); 
}