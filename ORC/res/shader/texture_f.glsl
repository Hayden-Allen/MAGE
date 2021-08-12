#version 330 core
layout(location = 0) out vec4 o_color;

uniform vec2 u_offset;
uniform sampler2D u_texture;

in vec2 v_tex;

void main()
{
	o_color = texture(u_texture, v_tex + u_offset);
}