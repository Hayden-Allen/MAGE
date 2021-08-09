#version 330 core
layout(location = 0) out vec4 o_color;

in vec2 i_tex;

// uniform sampler2D u_texture;

void main()
{
	// o_color = texture(u_texture, i_tex);
	o_color = vec4(i_tex, 0, 1);
}