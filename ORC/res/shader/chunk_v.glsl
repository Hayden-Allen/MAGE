#version 330 core
layout(location = 0) in vec2 i_pos;
layout(location = 1) in vec2 i_tex_coord;
layout(location = 2) in float i_sprite_index;

uniform mat4 u_view_projection;

out vec2 v_tex_coord;
out float v_sprite_index;

void main()
{
	gl_Position = u_view_projection * vec4(i_pos, 0, 1);
	v_tex_coord = i_tex_coord;
	v_sprite_index = i_sprite_index;
}