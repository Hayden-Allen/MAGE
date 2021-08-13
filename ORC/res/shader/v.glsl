#version 330 core
layout(location = 0) in vec2 i_pos;

uniform mat4 u_camera;

void main()
{
	gl_Position = u_camera * vec4(i_pos, 0, 1);
}