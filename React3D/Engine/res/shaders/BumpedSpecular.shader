#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_texCoord;
out vec3 v_normal;
out vec3 v_fragPos;

uniform mat4 u_view;
uniform mat4 u_model;
uniform mat4 u_projection;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(position, 1.0f);
	v_texCoord = texCoord;
	v_fragPos = vec3(u_model * vec4(position, 1.0f));
	v_normal = mat3(transpose(inverse(u_model))) * normal;
};

#shader fragment
#version 330 core
#define MAX_POINT_LIGHTS 8

layout(location = 0) out vec4 color;

struct DirLight
{
	vec3	direction;
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	vec3	color;
};
struct PointLight
{
	vec3	position;
	float	constant;
	float	linear;
	float	quadratic;
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	vec3	color;
};
struct SpotLight
{
	vec3	position;
	vec3	direction;
	float	cutOff;
	float	outerCutOff;
	float	constant;
	float	linear;
	float	quadratic;
	vec3	ambient;
	vec3	diffuse;
	vec3	specular;
	vec3	color;
};

in vec2 v_texCoord;
in vec3 v_normal;
in vec3 v_fragPos;

uniform vec3			x_viewPos;
uniform int				x_pointLightsCount;
uniform DirLight		x_dirLight;
uniform PointLight		x_pointLights[MAX_POINT_LIGHTS];
uniform SpotLight		x_spotLight;
uniform sampler2D		u_albedo;
uniform sampler2D		u_normalMap;
uniform vec4			u_color;
uniform float			u_blend;
uniform float			u_shininess;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 texColor);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec4 texColor);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec4 texColor);

void main()
{
	vec4 texColor = texture(u_albedo, v_texCoord);
	
	vec3 norm = normalize(v_normal);
	vec3 viewDir = normalize(x_viewPos - v_fragPos);
	vec3 resLight = CalcDirLight(x_dirLight, norm, viewDir, texColor);
	for (int i = 0; i < x_pointLightsCount; i++)
		resLight += CalcPointLight(x_pointLights[i], norm, viewDir, texColor);
	resLight += CalcSpotLight(x_spotLight, norm, viewDir, texColor);

	float blendInverse = 1.0 - u_blend;
	color = vec4((texColor.r * blendInverse + u_color.r * u_blend) * resLight.r,
		(texColor.g * blendInverse + u_color.g * u_blend) * resLight.g,
		(texColor.b * blendInverse + u_color.b * u_blend) * resLight.b,
		texColor.a * blendInverse + u_color.a * u_blend);
};

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec4 texColor)
{
	vec3 ambient = light.ambient * light.color;
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.color * vec3(texColor);	
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);
	vec3 specular = light.specular * spec * light.color * vec3(texture(u_normalMap, v_texCoord));

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec4 texColor)
{
	vec3 ambient = light.ambient * light.color;
	vec3 lightDir = normalize(light.position - v_fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.color * vec3(texColor);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);
	vec3 specular = light.specular * spec * light.color * vec3(texture(u_normalMap, v_texCoord));
	float distance = length(light.position - v_fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec4 texColor)
{
	vec3 ambient = light.ambient * light.color;
	vec3 lightDir = normalize(light.position - v_fragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * light.color * vec3(texColor);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);
	vec3 specular = light.specular * spec * light.color * vec3(texture(u_normalMap, v_texCoord));
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = (light.cutOff - light.outerCutOff);
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	diffuse *= intensity;
	specular *= intensity;

	return (ambient + diffuse + specular);
}