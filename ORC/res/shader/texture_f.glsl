#version 330 core
layout(location = 0) out vec4 o_color;

uniform int u_frame;
uniform sampler2DArray u_texture;

in vec2 v_tex;

void main()
{
	o_color = texture(u_texture, vec3(v_tex, u_frame));
}