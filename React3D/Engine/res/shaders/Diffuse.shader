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

uniform vec3		lightPos;
uniform vec3		lightDirection;
uniform vec3		lightColor;
uniform sampler2D	u_albedo;
uniform vec4		u_color;
uniform float		u_blend;
uniform float		u_ambience;

void main()
{
	vec3 ambient = u_ambience * lightColor;

	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(lightPos - v_FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 resLight = ambient + diffuse;
	vec4 texColor = texture(u_albedo, v_TexCoord);
	float blendInverse = 1.0 - u_blend;
	color = vec4((texColor.r * blendInverse + u_color.r * u_blend) * resLight.r,
		(texColor.g * blendInverse + u_color.g * u_blend) * resLight.g,
		(texColor.b * blendInverse + u_color.b * u_blend) * resLight.b,
		texColor.a * blendInverse + u_color.a * u_blend);
};