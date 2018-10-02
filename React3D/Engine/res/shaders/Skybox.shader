#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

out vec3 v_texCoord;

uniform mat4 u_projection;
uniform mat4 u_view;

void main()
{
	vec4 pos = u_projection * u_view * vec4(position, 1.0f);
	gl_Position = pos.xyww;
	v_texCoord = position;
};

#shader fragment
#version 330 core

in vec3 v_texCoord;

out vec4 color;

uniform samplerCube skybox;

void main()
{
	color = texture(skybox, v_texCoord);
};