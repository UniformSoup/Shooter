#version 330 core
layout (location = 0) in vec3 pos;
uniform mat4 model = mat4(1.f), view, projection;

void main()
{
	gl_Position = projection * view * model * vec4(pos.x, pos.y, pos.z, 1.0);
}