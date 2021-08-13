#version 330 core
layout(location = 0) out vec4 o_color;

uniform sampler2D u_textures[32];
// TODO put these in a uniform buffer
uniform int u_tex_indices[32];
uniform vec2 u_offsets[32];

in vec2 v_tex_coord;
in float v_sprite_index;

void main()
{
	int si = int(v_sprite_index);
	o_color = texture(u_textures[u_tex_indices[si]], v_tex_coord + u_offsets[si]);
}