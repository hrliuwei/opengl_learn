#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{    
    FragColor = texture(texture1, TexCoords);
	//vec4 co = texture(texture1,TexCoords);
	//if(co.a < 0.1)
		//discard;
	//FragColor = co;
}