#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_view;
uniform mat4 u_model;
uniform mat4 u_projection;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(position, 1.0f);
	v_TexCoord = texCoord;
	v_FragPos = vec3(u_model * vec4(position, 1.0f));
	v_Normal = mat3(transpose(inverse(u_model))) * normal;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3		l_view;
uniform vec3		l_pos;
uniform vec3		l_dir;
uniform vec3		l_color;
uniform float		l_constant;
uniform float		l_linear;
uniform float		l_quadratic;
uniform float		l_cutoff;
uniform float		l_outercutoff;
uniform int			l_type;
uniform sampler2D	u_albedo;
uniform sampler2D	u_normalmap;
uniform vec4		u_color;
uniform float		u_blend;
uniform float		u_ambience;
uniform float		u_specular;

void main()
{
	vec4 texColor = texture(u_albedo, v_TexCoord);

	vec3 ambient = u_ambience * l_color;
	vec3 norm = normalize(v_Normal);

	vec3 lightDir = vec3(0.0, 0.0, 0.0);
	if (l_type == 0) lightDir = normalize(-l_dir);
	else lightDir = normalize(l_pos - v_FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * l_color * vec3(texColor);

	vec3 viewDir = normalize(l_view - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = u_specular * spec * l_color * vec3(texture(u_normalmap, v_TexCoord));

	if (l_type == 1)
	{
		float distance = length(l_pos - v_FragPos);
		float attenuation = 1.0f / (l_constant + l_linear * distance + l_quadratic * (distance * distance));
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;
	}
	else if (l_type == 2)
	{
		float theta = dot(lightDir, normalize(-l_dir));
		float epsilon = (l_cutoff - l_outercutoff);
		float intensity = clamp((theta - l_outercutoff) / epsilon, 0.0, 1.0);
		diffuse *= intensity;
		specular *= intensity;
	}

	vec3 resLight = ambient + diffuse + specular;
	float blendInverse = 1.0 - u_blend;
	color = vec4((texColor.r * blendInverse + u_color.r * u_blend) * resLight.r,
		(texColor.g * blendInverse + u_color.g * u_blend) * resLight.g,
		(texColor.b * blendInverse + u_color.b * u_blend) * resLight.b,
		texColor.a * blendInverse + u_color.a * u_blend);
};