#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_view;
uniform mat4 u_model;
uniform mat4 u_projection;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(position, 1.0f);
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_albedo;
uniform vec4 u_color;
uniform float u_blend;

void main()
{
	vec4 texColor = texture(u_albedo, v_TexCoord);
	float blendInverse = 1.0 - u_blend;
	color = vec4(texColor.r * blendInverse + u_color.r * u_blend,
		texColor.g * blendInverse + u_color.g * u_blend,
		texColor.b * blendInverse + u_color.b * u_blend,
		texColor.a * blendInverse + u_color.a * u_blend);
};