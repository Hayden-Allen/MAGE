#version 330 core
layout(location = 0) out vec4 o_color;

uniform vec3 u_color;
uniform sampler2D u_texture;

in vec2 v_tex;

void main()
{
	o_color = mix(vec4(u_color, 1), texture(u_texture, v_tex), .5);
}