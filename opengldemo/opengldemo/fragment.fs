#version 330 core
struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light{
	vec3 positon;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in  vec3 Normal;
in  vec3 FragPos;
out vec4 FragColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform Material material;
uniform Light light;
void main()
{
	vec3 ambient = light.ambient * material.ambient;
	
	vec3 normal = normalize(Normal);
	vec3 lightv = normalize(lightPos - FragPos);
	float diff = max(dot(lightv, normal), 0);
	vec3 diffuse = (diff * material.diffuse) * light.diffuse;
	
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightv,normal);
	float spec = pow(max(dot(viewDir, reflectDir),0),material.shininess);
	vec3 specuse = (spec * material.specular) * light.specular;
	
	vec3 result = ambient + diffuse + specuse;
	FragColor = vec4(result,1.0);
};