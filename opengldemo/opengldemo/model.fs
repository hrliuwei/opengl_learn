#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform vec3      viewPos;

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

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos);

void main()
{    
    vec3 norm = normalize(normal);
	vec3 viewDir = normalize(viewPos - fragPos);
	//点光源
	vec3 result;
	for(int i = 0; i < NR_POINT_LIGHHT; i++)
	{
		result += CalcPointLight(pointLights[i], norm, viewDir, fragPos);
	}
	FragColor = vec4(result, 1.0);
	//FragColor = vec4(texture(texture_diffuse1,TexCoords));
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
	vec3 lightDir = normalize(light.positon - fragPos);
	//漫反射
	float diff = max(dot(normal, lightDir), 0.0);
	//镜面光
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
	//衰减
	float distance = length(light.positon - fragPos);
	float attenuation = 1.0/(light.constant + light.linear*distance + light.quadratic*distance*distance);
	//合并
	vec3 ambient = light.ambient*vec3(texture(texture_diffuse1, TexCoords));
	vec3 diffuse = light.diffuse*diff*vec3(texture(texture_diffuse1, TexCoords));
	vec3 specular = light.specular*spec*vec3(texture(texture_specular1, TexCoords));
	return (ambient + diffuse + specular);
}