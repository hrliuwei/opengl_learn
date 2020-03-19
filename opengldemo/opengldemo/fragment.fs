#version 330 core
struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light{
	//vec3 positon;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in  vec2 texCoords;
in  vec3 Normal;
in  vec3 FragPos;
out vec4 FragColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform Material material;
uniform Light light;
void main()
{
	vec3 lightDir = normalize(-light.direction);
	
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
	
	vec3 normal = normalize(Normal);
	//vec3 lightv = normalize(lightPos - FragPos);
	float diff = max(dot(lightDir, normal), 0);
	vec3 diffuse = (diff * vec3(texture(material.diffuse,texCoords))) * light.diffuse;
	
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir, reflectDir),0),material.shininess);
	vec3 specuse = (spec * vec3(texture(material.specular,texCoords))) * light.specular;
	
	vec3 result = ambient + diffuse + specuse;
	FragColor = vec4(result,1.0);
};