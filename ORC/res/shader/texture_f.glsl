#version 330 core
layout(location = 0) out vec4 o_color;

uniform vec2 u_offset;
uniform int u_index;
uniform sampler2D u_textures[32];

in vec2 v_tex;

void main()
{
	o_color = texture(u_textures[u_index], v_tex + u_offset);
}