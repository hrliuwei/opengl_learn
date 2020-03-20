#version 330 core
struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light{
	vec3 positon;
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float Linear;
	float quadratic;
	
	float cutOff;
	float outerCutOff;
};

struct DirLight{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dirLight;

struct PointLight{
	vec3 positon;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float constant;
	float linear;
	float quadratic;
};
#define NR_POINT_LIGHHT 4
uniform PointLight pointLights[NR_POINT_LIGHHT];

struct SpotLight{
	vec3 positon;
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	float cutOff;
	float outerCutOff;
};
uniform SpotLight spotLight;

in  vec2 texCoords;
in  vec3 Normal;
in  vec3 FragPos;
out vec4 FragColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos);




void main()
{
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	//定向光
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	//点光源
	for(int i = 0; i < NR_POINT_LIGHHT; i++)
	{
		result += CalcPointLight(pointLights[i], norm, viewDir, FragPos);
	}
	//聚光
	result += CalcSpotLight(spotLight, norm, viewDir, FragPos);
	FragColor = vec4(result, 1.0);
};


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	//漫反射
	float diff = max(dot(normal, lightDir), 0.0);
	//镜面光
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0), material.shininess);
	//合并
	vec3 ambient = light.ambient*vec3(texture(material.diffuse, texCoords));
	vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse, texCoords));
	vec3 specular = light.specular*spec*vec3(texture(material.specular, texCoords));
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
	vec3 lightDir = normalize(light.positon - fragPos);
	//漫反射
	float diff = max(dot(normal, lightDir), 0.0);
	//镜面光
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//衰减
	float distance = length(light.positon - fragPos);
	float attenuation = 1.0/(light.constant + light.linear*distance + light.quadratic*distance*distance);
	//合并
	vec3 ambient = light.ambient*vec3(texture(material.diffuse, texCoords));
	vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse, texCoords));
	vec3 specular = light.specular*spec*vec3(texture(material.specular, texCoords));
	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
	vec3 lightDir = normalize(light.positon - fragPos);
	//漫反射
	float diff = max(dot(normal, lightDir), 0.0);
	//镜面光
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//聚光
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff)/epsilon, 0.0 ,1.0);
	//合并
	vec3 ambient = light.ambient*vec3(texture(material.diffuse, texCoords));
	vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse, texCoords));
	vec3 specular = light.specular*spec*vec3(texture(material.specular, texCoords));
	return (ambient + diffuse + specular)*intensity;
}


